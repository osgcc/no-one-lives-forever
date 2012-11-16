#if !defined(_ZTOOLS_H_)
#define _ZTOOLS_H_

#include "string.h"
#include "dos.h"
#include "stdlib.h"
#include "errno.h"
#include "io.h"
#include "time.h"
#include "stddef.h"


class ostream;
class istream;


#ifndef NO_PRAGMA_LIBS
	#ifdef _DEBUG
		#pragma comment (lib, "\\proj\\libs\\debug\\ztools.lib")
	#else
		#pragma comment (lib, "\\proj\\libs\\release\\ztools.lib")
	#endif
#endif

	

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif




inline void* operator new(size_t size, void *ptr, int dummy1, int dummy2)
{
	return ptr;
}



//////////////////////////////////////////////////////////////////////////////

typedef void (*erf_t)(const char *, int);
unsigned long __caller_ip();
unsigned long __ip();

class zMinErr {
friend class zErrHandler;
friend class zErrHandling;
public:
    zMinErr();
    static erf_t set_erf(erf_t f) { erf_t t = ef; ef = f; return t; }
    static void quiet() { _quiet = 1; }
    static void use_error_function() { _quiet = 0; }
    static unsigned long caller() { return caller_ip; }
protected:
    static void handle(const char *s, int e)
        { caller_ip = __caller_ip(); if (_quiet) errno = e; else ef(s,e); }
    static void handle_inl(const char *s, int e)
        { caller_ip = __ip(); if (_quiet) errno = e; else ef(s,e); }
private:
    static unsigned long caller_ip;
    static erf_t ef;
    static int _quiet;
    static void catcher(const char *, int);
};



//////////////////////////////////////////////////////////////////////////////



const int MAX_DEDICATED = 32;

class _dhandler {   // dedicated error handler descriptor
friend class zErrHandler;
    void *object;
    erf_t handler;
    short lasterr;
};

class zErrHandler {
friend class zErrHandling;
friend class zErrHandler_default;
public:
    enum error_mode { logging = 1, fcall = 2, quickest = 4, exception = 8 };
    zErrHandler(const char *);
	error_mode setmode(error_mode em)
		{ prevmode = mode; mode = em; return error_mode(prevmode); }
protected:
    void log() { prevmode = mode; mode = logging; }
                // log error no - user must check
    void callfunc() { prevmode = mode; mode = fcall; }
                // call error function
//  void exceptions() { prevmode = mode; mode = exception; }
                // some day?
    void fast() { prevmode = mode; mode = quickest; }
    void prevstate() { mode = prevmode; }
    void handle(void *, const char *, int);
    int geterr(void *, int = 0);
    int ok_set_ef() { return ndh < MAX_DEDICATED; }
    erf_t set_ef(void *,erf_t);
    erf_t set_default_ef(erf_t);
private:
    int srch(void *);

    static _dhandler dl[MAX_DEDICATED];  // dedicated handler list
    static int ndh;

    erf_t default_ef;
    int slot;
    short evalue;
    int mode, prevmode;
    const char *id;
};

typedef zErrHandler::error_mode ehm_t;

// Class zErrHandling simply provides indirection to a zErrHandler
// object.  It can be used as a base class to provide the error
// handling capabilities of class zErrHandler, without adding much
// to the size of the object.

class zErrHandling {
public:
    virtual ~zErrHandling();
    void log() { hp->log(); }
    void callfunc() { hp->callfunc(); }
    void fast() { hp->fast(); }
    void prevstate() { hp->prevstate(); }
    void handle(const char *s, int e) const
        { zMinErr::caller_ip = __caller_ip(); hp->handle((void *) this,s,e); }
    void handle_inl(const char *s, int e) const
        { zMinErr::caller_ip = __ip(); hp->handle((void *) this,s,e); }
    int geterr() { return hp->geterr(this); }
    void reseterr(int n = 0) { hp->geterr(this,n); }
    int ok_set_ef() { return hp->ok_set_ef(); }
    erf_t set_ef(erf_t f) { return hp->set_ef(this,f); }
    erf_t set_default_ef(erf_t f) { return hp->set_default_ef(f); }

protected:

    zErrHandling(zErrHandler *p = 0);

// some common errors have preassigned strings
    static char *_nomem;
    static char *_inval;
    static char *_overflow;
    static char *_nosuch;
    static char *_range;
    static char *_exists;
    static char *_nullparg;
    static char *_badarg;

private:

    zErrHandler *hp;
};

typedef ehm_t (*classemf_t)(ehm_t);

class zSilent {
public:
	zSilent(zErrHandling *p) : func(0), handler(p)
		{ if (handler) handler->log(); }
	zSilent(classemf_t f) : handler(0), func(f)
		{ old = f(zErrHandler::logging); }
	~zSilent() { if (func) func(old); else if (handler) handler->prevstate(); }
private:
	zErrHandling *handler;
	classemf_t func;
	ehm_t old;
};



//////////////////////////////////////////////////////////////////////////////



// signature of general purpose visit function
typedef void (*vf_t)(void *, void *);		// visit function pointer
typedef void (*dtorf_t)(void *);    // explicit destructor function pointer

class zPtrColl {
public:
    enum cleanup_behaviour { passive = 0, none = 1, active = 2 };
    enum marker_validity { suspect = 4 };

    size_t count() const { return _count; }
    int valid() const { return !(flags & suspect); }
                                        // any attached markers ok?
    void noclean() { flags |= none; }   // suppress destruction

// In collections of pointers it will sometimes be necessary to test
// if two pointers address the same object.
    static int same(void *a, void *b);

    int purge() const { return flags & active; }
    int leave() const { return flags & none; }

    void makevalid() { flags &= ~suspect; }
    void invalidate() { flags |= suspect; }

    void incc() { ++_count; }
    void decc() { --_count; }
    void resetc(size_t v = 0) { _count = v; }

    void destroy(void *p) { dtor(p); }
	virtual ~zPtrColl();

protected:

    zPtrColl(cleanup_behaviour, dtorf_t);
	dtorf_t destructor() const { return dtor; }

private:

    dtorf_t dtor;
    short flags;
    size_t _count;
};

inline int zPtrColl::same(void *a, void *b)
	{ return (a == b); }




//////////////////////////////////////////////////////////////////////////////




class zList : public zPtrColl {
public:
    enum position { liststart, listend, before, after, cur };
    int empty() { return !count(); }
protected:
    zList(cleanup_behaviour cb, dtorf_t d) : zPtrColl(cb,d) {}
};




//////////////////////////////////////////////////////////////////////////////



typedef unsigned size_t;


/*
 Compares over n bytes from high memory to low
 Returns:
       > 0		if s1 > s2
       = 0		if s1 == s2
       < 0		if s1 < s2
*/
int memrcmp(const void *, const void *, unsigned);

/*
 Tests for non-zero over n bytes starting at s
 Returns:
		1		if n bytes starting at s contain a non-zero element
		0		otherwise

*/
int memtest(const void *, size_t);

/*
 Tests if two pointers point at same address
 in small and medium models use if (a == b) - no function call
 in large and compact model use same_address(a,b)
 Returns:
		1		if same address
		0		otherwise
*/
int same_address(const void *a, const void *b);





//////////////////////////////////////////////////////////////////////////////





const int UB = 8*sizeof(unsigned);
const int UPB = 8*sizeof(unsigned *);

class zBitSet : public zErrHandling {
friend ostream &operator<<(ostream&, const zBitSet&);
friend istream &operator>>(istream&, zBitSet&);

friend int operator==(const zBitSet&, const zBitSet&);
friend int operator==(const zBitSet&, unsigned);
friend int operator==(unsigned, const zBitSet&);
friend int operator!=(const zBitSet&, const zBitSet&);
friend int operator!=(unsigned, const zBitSet&);
friend int operator!=(const zBitSet&, unsigned);
friend int operator>(const zBitSet&, const zBitSet&);
friend int operator>(const zBitSet&, unsigned);
friend int operator<(const zBitSet&, const zBitSet&);
friend int operator<(unsigned, const zBitSet&);
friend int operator>=(const zBitSet&, const zBitSet&);
friend int operator>=(const zBitSet&, unsigned);
friend int operator>=(unsigned, const zBitSet&);
friend int operator<=(const zBitSet&, const zBitSet&);
friend int operator<=(unsigned, const zBitSet&);
friend int operator<=(const zBitSet&, unsigned);
friend zBitSet operator+(const zBitSet&, const zBitSet&);   // Union
friend zBitSet operator+(const zBitSet&, unsigned);
friend zBitSet operator+(unsigned, const zBitSet&);
friend zBitSet operator-(const zBitSet&, const zBitSet&);   // Difference
friend zBitSet operator-(const zBitSet&, unsigned);
friend zBitSet operator*(const zBitSet&, const zBitSet&);   // Intersection
friend zBitSet operator*(const zBitSet&, unsigned);
friend zBitSet operator*(unsigned, const zBitSet&);
friend zBitSet operator/(const zBitSet&, const zBitSet&);   // Disjunction
friend zBitSet operator/(const zBitSet&, unsigned);
friend zBitSet operator/(unsigned, const zBitSet&);
public:
    zBitSet();
    zBitSet(unsigned, unsigned = 0);
    zBitSet(unsigned *, int, unsigned = 0);
    zBitSet(const char *, unsigned = 0);
    zBitSet(const zBitSet&);
    ~zBitSet();

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

    zBitSet &operator=(const zBitSet&);
    zBitSet &operator+=(unsigned n)
    {
        return n >= max? extend(n):
            (*(body() + (n >> 5)) |= (1U << (n & 31)), *this);
    }
    zBitSet &operator+=(const zBitSet&);
    zBitSet &operator-=(unsigned n)
    {
        return n >= max? *this:
            (*(body() + (n >> 5)) &= ~(1U << (n & 31)), *this);
    }
    zBitSet &operator-=(const zBitSet&);

    int operator()(unsigned i) const
    {
        return i >= max? 0: ((*(body() + (i >> 5)) & (1U << (i & 31)))? 1: 0);
    }

    unsigned members() const { return bitcount(body(),max/UB); }
    int operator!() const
        { return !memtest(body(),max/8); }
    operator void *() const
        { return memtest(body(),max/8)? (void *) this: 0; }

    static unsigned set_default_capacity(unsigned n)
        { unsigned t = defcap; defcap = n; return t; }

    void dump() const;
private:
    static unsigned bitcount(unsigned *p, unsigned n);
    unsigned *body() const { return max > UPB? _body:
                                    (unsigned *) &_body; }
    zBitSet &extend(unsigned);
    int fixup(unsigned);
    int subset(const zBitSet&) const;
    int equal(const zBitSet&) const;
    int realloc(unsigned);
    static unsigned defcap;
    unsigned max;
    unsigned *_body;
	static zErrHandler ceh;
};

inline int operator==(const zBitSet &a, const zBitSet &b)
    { return a.equal(b); }
inline int operator==(const zBitSet &a, unsigned n)
    { return (a.members() == 1) && a(n); }
inline int operator==(unsigned n, const zBitSet &a)
    { return (a.members() == 1) && a(n); }
inline int operator!=(const zBitSet &a, const zBitSet &b)
    { return !a.equal(b); }
inline int operator!=(const zBitSet &a, unsigned n)
    { return (a.members() != 1) || !a(n); }
inline int operator!=(unsigned n, const zBitSet &a)
    { return (a.members() != 1) || !a(n); }
inline int operator>(const zBitSet &a, const zBitSet &b)
    { return b.subset(a) && !a.equal(b); }
inline int operator>(const zBitSet &a, unsigned n)
    { return (a.members() > 1) && a(n); }
inline int operator<(const zBitSet &a, const zBitSet &b)
    { return a.subset(b) && !a.equal(b); }
inline int operator<(unsigned n, const zBitSet &a)
    { return (a.members() > 1) && a(n); }
inline int operator>=(const zBitSet &a, const zBitSet &b)
    { return b.subset(a); }
inline int operator>=(const zBitSet &a, unsigned n) { return a(n) != 0; }
inline int operator>=(unsigned n, const zBitSet &a)
    { return (a.members() == 1) && a(n); }
inline int operator<=(const zBitSet &a, const zBitSet &b)
    { return a.subset(b); }
inline int operator<=(unsigned n, const zBitSet &a) { return a(n) != 0; }
inline int operator<=(const zBitSet &a, unsigned n)
    { return (a.members() == 1) && a(n); }
inline zBitSet operator+(const zBitSet &a, unsigned n)
    { zBitSet t = a; return t += n; }
inline zBitSet operator+(unsigned n, const zBitSet &a)
    { zBitSet t = a; return t += n; }
inline zBitSet operator-(const zBitSet &a, unsigned n)
    { zBitSet t = a; return t -= n; }
inline zBitSet operator*(const zBitSet &a, unsigned n)
    { zBitSet t; return a(n)? t += n: t; }
inline zBitSet operator*(unsigned n, const zBitSet &a)
    { zBitSet t; return a(n)? t += n: t; }
inline zBitSet operator/(unsigned n, const zBitSet &a)
    { return operator/(a,n); }



//////////////////////////////////////////////////////////////////////////////




typedef void (*dtorf_t)(void *);
typedef void (*vf_t)(void *, void *);


class zSLink {
	friend class zSList;			 // Members must be accessible to zSList
	friend class zSLCursor;		  // and to the associated cursor class
	friend class zSLFreeCache;

	zSLink(void *a) {body = a; next = 0; }
	void *operator new(size_t);
	void operator delete(void *);

	static zSLink *cache;

	static void freecache();

	zSLink* next;
	void *body;
};


class zSLFreeCache
{
public:
	~zSLFreeCache() { zSLink::freecache(); }
};


class zSList : public zMinErr {
	friend class zSLCursor;

public:
	zSList(dtorf_t df, void *item = 0);
	~zSList();

	int empty() const { return last? 0: 1; }
	void purge() { _clear(1); }
	void clear() { _clear(0); }

// append argument list to *this, list arg is cleared
	void merge(zSList &arg);

	dtorf_t set_dtor(dtorf_t f)
		{ dtorf_t t = dtor; dtor = f; return t; }
protected:
	void *append(void *);
	void *prepend(void *);

	void *head() const { return last? last->next->body: 0; }
	void *tail() const { return last? last->body: 0; }
	void *gethead();

	void traverse(vf_t, void*);

private:
	static int same(void *a, void *b)
		{ return (a == b); }
	void _clear(int);

	dtorf_t dtor;			// explicit destructor function pointer
	zSLink* last;			// last->next is head of list

	zSLFreeCache cachedestructor;
};

class zSLCursor {
public:
	enum position { after, before };
	zSLCursor(zSList&);
	int first() const { return list.last && zSList::same(cp,list.last->next); }
	int last() const { return list.last && zSList::same(cp,list.last); }
	int empty() const { return list.last? 0: 1; }
protected:
	void *current() const { return cp ? cp->body : 0; }
	void *next()
	{
		return list.last? (zSList::same(cp,list.last)?
			0: (pp = cp, cp = cp->next, cp->body)): 0;
	}
	void *reset()
	{
		return list.last? (pp = list.last, cp = pp->next, cp->body): 0;
	}
	void *remove();
	void *insert(void *, position = after);
private:
	zSList &list;
	zSLink *cp, *pp;
};

template<class T> class zGSList : public zSList {
public:
	zGSList(T *a = 0) : zSList((dtorf_t) dtf, a) {}
	T *append(T *a) { return (T *) zSList::append(a); }
	T *prepend(T *a) { return (T *) zSList::prepend(a); }
	T *head() const { return (T *) zSList::head(); }
	T *tail() const { return (T *) zSList::tail(); }
	T *gethead() { return (T *) zSList::gethead(); }
	void traverse(void (*vf)(T*, void *), void *supplementary = 0)
		{ zSList::traverse((vf_t) vf, supplementary); }

private:
	static void dtf(T *);
	zGSList(const zGSList<T> &);
	zGSList<T> &operator=(const zGSList<T> &);
};

//#ifdef __zGSList_Expand_Template_Functions
template<class T> void zGSList<T>::dtf(T *p)
{
	p->~T();
}
//#endif

template<class T> class zGSLCursor : public zSLCursor {
public:
	zGSLCursor(zSList &a) : zSLCursor(a) {}
	T *operator()() { return (T *) zSLCursor::current(); }
	T *current() { return (T *) zSLCursor::current(); }
	T *next() { return (T *) zSLCursor::next(); }
	T *reset() { return (T *) zSLCursor::reset(); }
	T *insert(T *a, position r = zSLCursor::after)
		 { return (T *) zSLCursor::insert(a, r); }
	T *remove() { return (T *) zSLCursor::remove(); }
};




//////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
//
// AVL (Adelson-Velski and Landis) trees are the 'standard' computer
// science version of balanced binary trees.  This interface describes
// general purpose AVL trees
//

typedef int (*cmpf_t)(void *, void *);

class zAVLnode {
friend class zAVLTree;
    zAVLnode* &ptr(int a) { return (a < 0)? left: right; }
    zAVLnode *left, *right;
    void *body;
    signed char balance;
};

class zAVLpath {
friend class zAVLTree;
    zAVLpath() { level = 0; }
    void push(zAVLnode* p, int d)
        { ptr[level] = p; descent[level] = d; ++level; }
    void pop(zAVLnode* &p, int &d)
        { --level; p = ptr[level]; d = descent[level]; }
    int level;
    zAVLnode *ptr[32];
    int descent[32];
};

class zAVLTree : public zPtrColl, public zErrHandling {
public:
    enum order { inorder, revorder, preorder, postorder };
    enum direction { higher = +1, lower = -1 };

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

// These are AVL tree debugging/display facilities
    void dump(zAVLnode *p = 0) const;
    void draw(zAVLnode *p = 0, int = 0, int = 0, int = 0) const;
    int checkAVL(zAVLnode *p = 0) const;
protected:
    zAVLTree(dtorf_t, cmpf_t, cleanup_behaviour = zPtrColl::passive);
    ~zAVLTree() { if (!leave()) cleanup(); }
    void *insert(void *);
    void *remove(void *);
    int concatenate(zAVLTree &);
    void *lookup(void *) const;
    void *seek(void*, zAVLTree::direction = higher) const;
    void *max() const;
    void *min() const;
    void traverse(vf_t vf, void *supplementary, zAVLTree::order o)
		{ _trav(vf, supplementary, o, root); }

private:
    static zAVLnode *rotate(zAVLnode *, int);
    void _trav(vf_t, void *, zAVLTree::order, zAVLnode * = 0);
    static int concat(zAVLTree &a, zAVLTree &b, zAVLnode *);
    void cleanup(zAVLnode * = 0);
    int depth(zAVLnode*) const;
    zAVLnode *root;
    cmpf_t cf;
	static zErrHandler ceh;
};

template<class T> class zGAVLTree : public zAVLTree {
public:
    zGAVLTree(int (*f)(T*, T*), cleanup_behaviour cb = zPtrColl::passive)
         : zAVLTree((dtorf_t) dtf,(cmpf_t) f,cb) {}
    T *insert(T *a) { return (T *) zAVLTree::insert(a); }
    T *remove(T *a) { return (T *) zAVLTree::remove(a); }
    T *lookup(T *a) const { return (T *) zAVLTree::lookup(a); }
	T *seek(T *a, zAVLTree::direction r = zAVLTree::higher) const
		{ return (T *) zAVLTree::seek(a,r); }
    T *min() const { return (T *) zAVLTree::min(); }
    T *max() const { return (T *) zAVLTree::max(); }
    void traverse(void (*vf)(T*, void*), void *supplementary = 0,
						zAVLTree::order o = inorder)
        { zAVLTree::traverse((vf_t) vf,supplementary,o); }
    int concatenate(zGAVLTree<T> &a) { return zAVLTree::concatenate(a); }
private:
    static void dtf(T *);
    zGAVLTree(const zGAVLTree<T> &);
    zGAVLTree<T> &operator=(const zGAVLTree<T> &);
};

//#ifdef __zGAVLTree_Expand_Template_Functions
template<class T> void zGAVLTree<T>::dtf(T *p)
{
    p->~T();
}
//#endif




//////////////////////////////////////////////////////////////////////////////





//typedef void (*vf_t)(void *, void *);			// visit function pointer

class zDLNode {
	friend class zDList;
	friend class zDLCursor;
	zDLNode *next, *prev;	// pointers to next and previous items in list
	void *body;				// points to whatever is associated with this node
};

class zDList : public zList, public zErrHandling {
	friend class zDLCursor;

public:

	int first() const { return same(cp,root->next); }
	int last() const { return same(cp,root); }

	void clear() { cleanup(); cp = root = 0; }

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

protected:
	zDList(dtorf_t, cleanup_behaviour = zPtrColl::passive);
	zDList(dtorf_t, void* item, cleanup_behaviour = zPtrColl::passive);
	~zDList() { if (!leave()) cleanup(); }

	void *insert(void *item, zList::position);
	void *remove(zList::position);
	void *update(void *);

	void *setfirst() { return root? (cp = root->next, cp->body): 0; }
	void *setlast() { return root? (cp = root, cp->body): 0; }
	void *move(int);

	void *head() const { return root? root->next->body: 0; }
	void *tail() const { return root? root->body: 0; }

	void *gethead() { return remove(zList::liststart); }
	void *gettail() { return remove(zList::listend); }

	void *current() const { return root? cp->body: 0; }

	void merge(const zDList&);

	void traverse(vf_t vf, void *) const;

private:
	void cleanup();
	zDLNode *root;			 // root->next points at head of list root at tail
	zDLNode *cp;			 // remembers current context
	static zErrHandler ceh;
};

// The cursor class reproduces the movement and access capabilities
// of the list currency.
class zDLCursor {
public:
	int first() const { return zPtrColl::same(cp,thislist.root->next); }
	int last() const { return zPtrColl::same(cp,thislist.root); };

	void sync() { cp = thislist.cp; }
	int insync() const { return zPtrColl::same(cp,thislist.cp); }
	int valid() const { return thislist.valid(); }
	int empty() const { return thislist.empty(); }

protected:
// The constructor takes a reference to a zDList as argument.  The optional
// argument determines the relationship of the cursor currency to the
// zDList currency.
	zDLCursor(zDList&, zList::position = zList::cur);

	void *insert(void *item, zList::position = zList::after);
	void *remove(zList::position = zList::cur);
	void *update(void *);

	void *setfirst()\
		{ return thislist.valid()? (cp = thislist.root->next, cp->body): 0; }\
	void *setlast()\
		{ return thislist.valid()? (cp = thislist.root, cp->body): 0; }\
	void *move(int n);

	void *current() const { return thislist.valid()? cp->body: 0; }

	zDList &thislist;	 // list this cursor is riding
	zDLNode *cp;
};


template<class T> class zGDList : public zDList {
public:
	zGDList(cleanup_behaviour cb = zPtrColl::passive)
		: zDList((dtorf_t) dtf,cb) {}
	zGDList(T *a, cleanup_behaviour cb = zPtrColl::passive)
		: zDList((dtorf_t) dtf,a,cb) {}
	T *append(T *a) { return (T *) zDList::insert(a, zList::listend); }
	T *prepend(T *a) { return (T *) zDList::insert(a, zList::liststart); }
	T *head() const { return (T *) zDList::head(); }
	T *tail() const { return (T *) zDList::tail(); }
	T *gethead() { return (T *) zDList::remove(zList::liststart); }
	T *gettail() { return (T *) zDList::remove(zList::listend); }
	T *insert(T *a, zList::position r = zList::before)
		{ return (T *) zDList::insert(a,r); }
	T *remove(zList::position r = zList::cur)
		{ return (T *) zDList::remove(r); }
	T *update(T *a)
		{ return (T *) zDList::update(a); }
	T *current() const { return (T *) zDList::current(); }
	T *operator()() const { return (T *) zDList::current(); }
	T *next() { return (T *) zDList::move(1); }
	T *operator++() { return (T *) zDList::move(1); }
	T *operator++(int)
		{ T *t = (T *) zDList::current(); zDList::move(1); return t; }
	T *operator+=(int n) { return (T *) zDList::move(n); }
	T *prev() { return (T *) zDList::move(-1); }
	T *operator--() { return (T *) zDList::move(-1); }
	T *operator--(int)
		{ T *t = (T *) zDList::current(); zDList::move(-1); return t; }
	T *operator-=(int n) { return (T *) zDList::move(-n); }
	T *setfirst() { return (T *) zDList::setfirst(); }
	T *setlast() { return (T *) zDList::setlast(); }
	void traverse(void (*vf)(T*, void*), void *supplementary = 0) const
		{ zDList::traverse((vf_t) vf, supplementary); }
private:
	static void dtf(T*);
	zGDList(const zGDList<T>&);
	zGDList<T> &operator=(const zGDList<T>&);
};

//#ifdef __zGDList_Expand_Template_Functions
template<class T> void zGDList<T>::dtf(T *p)
{
	p->~T();
}
//#endif

template<class T> class zGDLCursor : public zDLCursor {
public:
	zGDLCursor(zDList& a, zList::position s = zList::cur)
				: zDLCursor(a, s) {}
	T *insert(T *a, zList::position r = zList::after)
		{ return (T *) zDLCursor::insert(a,r); }
	T *remove(zList::position r = zList::cur)
		{ return (T *) zDLCursor::remove(r); }
	T *update(T *a)
		{ return (T *) zDLCursor::update(a); }
	T *current() { return (T *) zDLCursor::current(); }
	T *operator()() { return (T *) zDLCursor::current(); }
	T *setfirst() { return (T *) zDLCursor::setfirst(); }
	T *setlast() { return (T *) zDLCursor::setlast(); }
	T *next() { return (T *) zDLCursor::move(1); }
	T *operator++() { return (T *) zDLCursor::move(1); }
	T *operator++(int)
		{ T *t = (T *) zDLCursor::current(); zDLCursor::move(1); return t; }
	T *operator+=(int n) { return (T *) zDLCursor::move(n); }
	T *prev() { return (T *) zDLCursor::move(-1); }
	T *operator--()
		{ T *t = (T *) zDLCursor::current(); zDLCursor::move(-1); return t; }
	T *operator--(int) { return (T *) zDLCursor::move(-1); }
	T *operator-=(int n) { return (T *) zDLCursor::move(-n); }
	T *move(int n) { return (T *) zDLCursor::move(n); }
};




//////////////////////////////////////////////////////////////////////////////




typedef unsigned (*hashfunc_t)(void *, unsigned);
typedef int (*cmpf_t)(void *, void *);

class zHashTable : public zPtrColl, public zErrHandling {

public:
	enum mode { unique = 0, stacking = 1, queueing = 2 };
	void merge(zHashTable &);
	void clear();
	static unsigned default_hash(const char *, unsigned);
	static void report(zHashTable &, const char *(*xlate)(void *));
	static unsigned pow2(long);

	static ehm_t class_error_mode(ehm_t em)	{ return ceh.setmode(em); }

protected:
	zHashTable(dtorf_t, cmpf_t, int tablesize,hashfunc_t, 
		       cleanup_behaviour = zPtrColl::passive, 
			   mode = unique);
	~zHashTable();

	void* lookup(void *) const;
	void *insert(void *);
	void *remove(void *);
	void traverse(vf_t, void*) const;

private:
	mode _mode;
	zGSList<char> **table;
	unsigned tabsize;
	hashfunc_t hashfunc;
	cmpf_t cf;
	static zErrHandler ceh;
};

template<class T> class zGHashTable : public zHashTable {
public:
	zGHashTable(int (*f)(T*, T*), int tablesize,unsigned (*hf)(T*, unsigned),
		 cleanup_behaviour cb = zPtrColl::passive)
		  : zHashTable((dtorf_t) dtf,(cmpf_t) f,tablesize,(hashfunc_t) hf,cb) {}
	T *lookup(T *d)
		{ return (T *) zHashTable::lookup(d); }
	T *insert(T *d)
		{ return (T *) zHashTable::insert(d); }
	T *remove(T *d)
		{ return (T *) zHashTable::remove(d); }
	void traverse(void (*vf)(T*, void*), void *p = 0) const
		{ zHashTable::traverse((vf_t) vf, p); }
private:
	static void dtf(T *);
	zGHashTable(const zGHashTable<T> &);
	zGHashTable<T> &operator=(const zGHashTable<T> &);
};

//#ifdef __zGHashTable_Expand_Template_Functions
template<class T> void zGHashTable<T>::dtf(T *p)
{
	p->~T();
}
//#endif

template<class T> class zGHashTableDS : public zHashTable {
public:
	zGHashTableDS(int (*f)(T*, T*), int tablesize,unsigned (*hf)(T*, unsigned),
		 cleanup_behaviour cb = zPtrColl::passive)
		  : zHashTable((dtorf_t) dtf,(cmpf_t) f,tablesize,(hashfunc_t) hf,cb,
						zHashTable::stacking) {}
	T *lookup(T *d)
		{ return (T *) zHashTable::lookup(d); }
	T *insert(T *d)
		{ return (T *) zHashTable::insert(d); }
	T *remove(T *d)
		{ return (T *) zHashTable::remove(d); }
	void traverse(void (*vf)(T*, void*), void *p = 0) const
		{ zHashTable::traverse((vf_t) vf, p); }
private:
	static void dtf(T *);
	zGHashTableDS(const zGHashTableDS<T> &);
	zGHashTableDS<T> &operator=(const zGHashTableDS<T> &);
};

//#ifdef __zGHashTable_Expand_Template_Functions
template<class T> void zGHashTableDS<T>::dtf(T *p)
{
	p->~T();
}
//#endif

template<class T> class zGHashTableDQ : public zHashTable {
public:
	zGHashTableDQ(int (*f)(T*, T*), int tablesize,unsigned (*hf)(T*, unsigned),
		 cleanup_behaviour cb = zPtrColl::passive)
		  : zHashTable((dtorf_t) dtf,(cmpf_t) f,tablesize,(hashfunc_t) hf,cb,
							zHashTable::queueing) {}
	T *lookup(T *d)
		{ return (T *) zHashTable::lookup(d); }
	T *insert(T *d)
		{ return (T *) zHashTable::insert(d); }
	T *remove(T *d)
		{ return (T *) zHashTable::remove(d); }
	void traverse(void (*vf)(T*, void*), void *p = 0) const
		{ zHashTable::traverse((vf_t) vf, p); }
private:
	static void dtf(T *);
	zGHashTableDQ(const zGHashTableDQ<T> &);
	zGHashTableDQ<T> &operator=(const zGHashTableDQ<T> &);
};

//#ifdef __zGHashTable_Expand_Template_Functions
template<class T> void zGHashTableDQ<T>::dtf(T *p)
{
	p->~T();
}
//#endif




//////////////////////////////////////////////////////////////////////////////




const int CHUNK = 32;

class zIAStack : public zErrHandling {
public:
    zIAStack(int minitems = CHUNK);
    ~zIAStack();

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

    void push(int n) { if (_count >= alloc) realloc(n); else sp[_count++] = n; }
    int pop() { return _count? sp[--_count]: 0; }
	int top() const { return _count? sp[_count]: 0; }
    int count() const { return _count; }
    static int setblock(int n) { int t = block; block = n; return t; }
private:
    void realloc(int n);

    static int block;
    int *sp;
    int _count;
    int alloc;
	static zErrHandler ceh;
};





//////////////////////////////////////////////////////////////////////////////




class _NFAnfa {
friend class zNFA;
    int lowest, initial, final;
};

class _NFAtransition {
friend class zNFA;
friend class zDFA;
    int edge, val, next1, next2;
};

class istream;

class zNFA : public zErrHandling {
friend class zDFA;
public:
    enum zNFA_tokens {
        null = -1,
        or,
        closure = -128,
        posclosure,
        zeroone,
        repeat,
        rparen,
        lparen,
        exclusion,
        charset,
        character,
        end,
        marker,
        error
    };

    zNFA();
    zNFA(const char *, int longest = 1,
            char lowest = ' ', char highest = '\x79');
    ~zNFA();

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

    zNFA &operator=(const char *);
    int operator()(const char *) const;

    void dump() const;

private:
    zNFA(const zNFA&);
    zNFA &operator=(const zNFA&);
    void expression();
    void term();
    void factor();
    void nexttok();
    int setstate(int,int,int,int,int = 0);
    void adjuststate(int,int);
    int realloc();
    int parseset();
    static int includes(const char *s, char c) { return strchr(s,c) != 0; }
    int getrepeat();
    void setlast(int a, int b, int c)
        { lastfactor.lowest = a; lastfactor.initial = b; lastfactor.final = c; }
    void backtrack(int,int,int,int);
    zBitSet e_closure(zBitSet &) const;
    zBitSet move(const zBitSet &, char) const;

    _NFAtransition *mt;
    int ct, state, maxstate, invalid;
    int laststate, ccs, cval, lc, hc, longest;
    _NFAnfa lastfactor;
    const char *cp;
    char *sets[20];
	static zErrHandler ceh;
};





//////////////////////////////////////////////////////////////////////////////





const int MAXSTATES = 32;
typedef void (*chandlerf_t)(int, char, void *);

class zDFA : public zErrHandling {
public:
    zDFA(const zNFA&, int = 1);
    zDFA(const int*, int = 1);
    ~zDFA();

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

    void setmode(int m) { longest = (m != 0); }

    int operator()(const char *) const;
    int process(const char *, chandlerf_t, void * = 0) const;
    istream &extract(istream&, chandlerf_t, void * = 0) const;

    int states() const { return nstates; }
    int characters() const { return alphabet; }
    int store_size() const
        { int t = packed(); return t < unpacked()? t: unpacked(); }
    int unpacked() const
        { return nstates*alphabet + alphabet + 3; }
    int packed() const;

    int store(int *) const;
    int store_as_is(int *) const;
    int pack(int *) const;

    void format(int = 0) const;
	void export() const;
    void dump() const;
private:
    void subset_construction(const zNFA&);
    int find_charset(const zNFA&);
    int realloc();
    int cset[256];
    int longest, alphabet, nstates, maxstates;
    int *dtran;
    zBitSet **dstates;
	static zErrHandler ceh;
};




//////////////////////////////////////////////////////////////////////////////




typedef int (*cmpf_t)(void*, void*);

class zPQbase : public zPtrColl, public zErrHandling {
public:

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

    void dump() const;
protected:
    zPQbase(dtorf_t, cmpf_t,
        cleanup_behaviour = zPtrColl::passive, size_t allocchunk = 16);
    ~zPQbase();
    int insert(void *);
    void *dequeue();
    void *front() const
	{ 
		if (!valid()) {
			handle(_inval,EINVAL);
			return 0;
		}
		if (!count())
			return 0;
		return heap[1];
	}
    size_t setchunk(size_t c) { size_t t = chunk; chunk = c; return t; }
private:
    void **heap;
    int spare;
    size_t chunk;
    cmpf_t cf;
	static zErrHandler ceh;
};

template<class T> class zPriorityQueue : public zPQbase {
public:
    zPriorityQueue(int (*f)(T*, T*),
            cleanup_behaviour cb = zPtrColl::passive, size_t cs = 16)
         : zPQbase((dtorf_t) dtf,(cmpf_t) f,cb,cs) {}
    int insert(T *a) { return zPQbase::insert(a); }
    T *dequeue() { return (T *) zPQbase::dequeue(); }
    T *front() const { return (T *) zPQbase::front(); }
private:
    static void dtf(T *);
    zPriorityQueue(const zPriorityQueue<T> &);
    zPriorityQueue<T> &operator=(const zPriorityQueue<T> &);
};

//#ifdef __zPriorityQueue_Expand_Template_Functions
template<class T> void zPriorityQueue<T>::dtf(T *p)
{
    p->~T();
}
//#endif





//////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
//
// Patricia tree - an efficient radix search tree suitable for variable
// length string keys.

// Symbol table visit function type
typedef (*stvf_t)(const char *, void *, void *);
// the visit function will be called with a pointer to the key,
// a pointer to the associated object and a supplementary
// pointer provided by the user of traverse.

class zPTreeNode {
friend class zPTree;
    zPTreeNode* &ptr(int d) { return d? right: left; }

    zPTreeNode *left, *right;
    int index;
    char* symbol;
    void *body;
};

class zPTree : public zErrHandling, public zPtrColl {
public:

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

    void clear() { cleanup(); root = 0; preview = 0; resetc(); }

    void draw(zPTreeNode * = 0, int = 0, int = 0, int = 0) const;
    void dump(zPTreeNode * = 0);
protected:
    zPTree(dtorf_t, cleanup_behaviour = zPtrColl::active);
    ~zPTree() { cleanup(); }

    void *insert(const char *, void *);
    void *lookup(const char *);
    void *add(const char *, void *);
    void _trav(stvf_t, void *supplementary, zPTreeNode *);

private:
    void cleanup(zPTreeNode * = 0);
    static int bit(const char *s, int n)
        { return s[n >> 3] & (1 << (n & 7)); }
    static int diffpos(const char *, const char *);

    zPTreeNode* root;
    zPTreeNode *p, *q;
    int sbits;
    int preview;
	static zErrHandler ceh;
};

template<class T> class zSymTab : public zPTree {
public:
    zSymTab(cleanup_behaviour cb = zPtrColl::active)
         : zPTree((dtorf_t) dtf,cb) {}
    T *insert(const char *s, T *a) { return (T *) zPTree::insert(s,a); }
    T *lookup(const char *s) { return (T *) zPTree::lookup(s); }
    T *add(const char *s, T *a) { return (T *) zPTree::add(s,a); }
	void traverse(void (*vf)(const char *, T*, void *),
										void *supplementary = 0)
		{ zPTree::_trav((stvf_t) vf, supplementary, 0); }
private:
    static void dtf(T *);
    zSymTab(const zSymTab<T> &);
    zSymTab<T> &operator=(const zSymTab<T> &);
};

//#ifdef __zSymTab_Expand_Template_Functions
template<class T> void zSymTab<T>::dtf(T *p)
{
    p->~T();
}
//#endif



//////////////////////////////////////////////////////////////////////////////




template <class T> class zQueue : public zSList {
public:
    zQueue(T *a = 0) : zSList((dtorf_t) dtf,a) {}
    T *enqueue(T *a) { return (T *) zSList::append(a); }
    T *dequeue() { return (T *) zSList::gethead(); }
    T *front() const { return (T *) zSList::head(); }
private:
	static void dtf(T *);
    zQueue(const zQueue<T> &);
    zQueue<T> &operator=(const zQueue<T> &);
};

//#ifdef __zQueue_Expand_Template_Functions
template<class T> void zQueue<T>::dtf(T *p)
{
	p->~T();
}
//#endif



//////////////////////////////////////////////////////////////////////////////


class zIQueue : public zSList {
public:
    zIQueue() : _count(0), zSList(dtf) {}
    void enqueue(int n) { ++_count; zSList::append((void *) n); }

    int dequeue() { _count = _count? _count-1: 0; return (int) zSList::gethead(); }
    int front() const { return  (int) zSList::head(); }
    int count() { return _count; }
private:
	static void dtf(void *);
    zIQueue(const zIQueue &);
    zIQueue &operator=(const zIQueue &);
    int _count;
};

inline void zIQueue::dtf(void *)
{}

//////////////////////////////////////////////////////////////////////////////




template<class T> class zStack : public zSList {
public:
    zStack(T *a = 0) :zSList((dtorf_t) dtf,a) {}
    T *push(T *a) { return (T *) zSList::prepend(a); }
    T *pop() { return (T *) zSList::gethead(); }
    T *top() const { return (T *) zSList::head(); }
private:
	static void dtf(T *);
    zStack(const zStack<T> &);
    zStack<T> &operator=(const zStack<T> &);
};

//#ifdef __zStack_Expand_Template_Functions
template<class T> void zStack<T>::dtf(T *p)
{
	p->~T();
}
//#endif




//////////////////////////////////////////////////////////////////////////////



class zILStack : public zSList {
public:
    zILStack() : _count(0), zSList(dtf) {}
    void push(int n) { ++_count; zSList::prepend((void *) n); }
    int pop() { _count = _count? _count-1: 0; return (int) zSList::gethead(); }
    int top() const { return (int) zSList::head(); }
    int count() { return _count; }
private:
	static void dtf(void *);
    zILStack(const zILStack &);
    zILStack &operator=(const zILStack &);
    int _count;
};

inline void zILStack::dtf(void *)
{}


//////////////////////////////////////////////////////////////////////////////




class zFileName : public zErrHandling {
public:
    enum zFileName_errors { baddrive = -1, colon = -2, noname = -3,
			badname = -4, badext = -5, badpath = -6, pathlength = -7,
			nullptr = -8, memory = -9, invalid = -9 };

// There are three constructors, a default constructor,
// one which takes a filename string as an argument,  and optionally
// allows characters to be excluded from the filename.  The default
// value for this second parameter is the list of characters which
// are officially prohibited from a DOS file name or extension.
// The final constructor is a copy constructor.
    zFileName();
    //zFileName(const char *,
    //        const char * = "\\ *+=[]:;\",.?/");
    zFileName(const char *,
            const char * = "\\*+=[]:;\",.?/");
    zFileName(const zFileName&);
    ~zFileName();

    zFileName& operator=(const zFileName&);

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

// The next set of functions give access to the constituent parts of
// the filename.
    char drive() const { return _drive; }
    const char *name() const { return _name; }
    const char *ext() const { return _ext; }
    const char *path() const { return _path; }

    int parse(const char *);
    int build(char drv, const char *pth ,
            const char *nm, const char *ex);

    const char *get() const;

    const char *operator()() const { return get(); };

    int exists() const;
    unsigned attribute() const;
    long size() const;
    time_t time() const;

private:
    static void errpos(int, char, zFileName*);
    static char maxdrive;
    static zDFA *dfa;
	static zErrHandler ceh;

    char *fn;
    const char *forbid;
    char _drive;
    char _path[_MAX_PATH];
    char _name[_MAX_FNAME];
    char _ext[_MAX_EXT];
    int epos;
};




//////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////
//
// File attibutes:  these are defined in io.h
//
// _A_NORMAL	/* Normal file - No read/write restrictions */
// _A_RDONLY	/* Read only file */
// _A_HIDDEN	/* Hidden file */
// _A_SYSTEM	/* System file */
// _A_SUBDIR	/* Subdirectory */
// _A_ARCH 		/* Archive file */
//

class zDirectory : public zErrHandling {
public:

    enum sort_flag { nosort = 0, sort = 1 };

    zDirectory(const char *spec = "*.*", sort_flag sf = sort);
    zDirectory(const char *path, const char *spec, sort_flag sf = sort);

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

    int count() const { return d.count(); }

    int first() { return count()? (d.setfirst(), cn = 0): -1; }
    int last() { return count()? (d.setlast(), cn = count()-1): -1; }
    int next() { return (count() && cn < count()-1)? (d.next(), cn++): -1; }
    int prev() { return (count() && cn)? (d.prev(), cn--): -1; }

    char *name() const { return count()? d()->name: 0; }
    time_t filetime() const { return count()? d()->time_write: -1; }
    long size() const { return count()? d()->size: -1; }
    unsigned attribute() const { return count()? d()->attrib: -1; }

private:
    static int cmp(_finddata_t *a, _finddata_t *b);
    zGDList<_finddata_t> d;
    int cn;
	static zErrHandler ceh;
    void open_sort(const char *spec);
    void open_nosort(const char *spec);
    short sf;

};




//////////////////////////////////////////////////////////////////////////////


// Bound Checked and Dynamic Arrays
//
// Steve Teale
// Copyright Symantec Corp 1991, 1992
// Revision date    8/1/91
//                  12/21/91    use zErrHandling
//					7/16/92		control template function expansion
//

//////////////////////////////////////////////////////////////////////////
//
//  zArray<type>    -   Bounds checked array
//  zEArray<type>   -   Extendable bounds checked array
//  zDArray<type>   -   Dynamically extending array
//  zBDArray<type>  -   Batchwise dynamically extending array
//


class _zvec : public zErrHandling {
friend class _zvec2D;
public:
    int high() const { return hi; }
    int low() const { return lo; }

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

protected:
    _zvec(size_t s, int l, int h, void *overflow);
    ~_zvec();
    void *get(int i)
    {
        return (i < lo || hi < i)? (handle_inl(_range,ERANGE), ovf):
                                vec+(i-lo)*size;
    }
    int lo, hi;
    char *vec;
    void *ovf;
    size_t size;
    static zErrHandler ceh;
};

class _zdvec : public _zvec {
protected:
    _zdvec(size_t s, int l, int h, void *overflow);
    void *get(int i)
    {
        initcount = 0;
        return (i < lo || i > hi)?
            (realloc(i)? vec+(size*(i-lo)): (handle_inl(_nomem,ENOMEM),ovf)):
                                vec+(size*(i-lo));
    }
    int realloc(int i, int batch = 0);
    void *init;
    int initcount;
};

class _zbdvec : public _zdvec {
protected:
    _zbdvec(size_t s, int l, int h, void *overflow, int batch);
    void *bget(int i)
    {
        initcount = 0;
        return (i < lo || i > hi)?
            (realloc(i, chunk)? vec+(size*(i-lo)):
                        (handle_inl(_nomem,ENOMEM),ovf)):
                                vec+(size*(i-lo));
    }
    int chunk;
};

template<class T> class zArray : public _zvec {
public:
    zArray(int low, int high, T *overflow = 0);
    ~zArray();
    T &operator[](int i) { return *((T *) get(i)); }
    T *recover() { return (T *) ovf; }
};

//#ifdef __zArray_Expand_Template_Functions
template<class T> zArray<T>::zArray(int h, int l, T *overflow)
    : _zvec(sizeof(T),h,l,overflow)
{
    T *p = (T *) vec;
    if (!p) return;
    for (int i = hi-lo+1; i--; ++p)
        T *t = new(p, 0, 0) T;
}

template<class T> zArray<T>::~zArray()
{
    T *p = (T *) vec;
    if (!p) return;
    for (int i = hi-lo+1; i--; ++p)
        p->~T();
}
//#endif

template<class T> class zEArray : public _zdvec {
public:
    zEArray(int low, int high, T *overflow = 0);
    ~zEArray();
    T &operator[](int i) { return *((T *) get(i)); }
    T *recover() { return (T *) ovf; }
    void extend(int l, int h);
};

//#ifdef __zEArray_Expand_Template_Functions
template<class T> zEArray<T>::zEArray(int h, int l, T *overflow)
    : _zdvec(sizeof(T),h,l,overflow)
{
    T *p = (T *) vec;
    if (!p) return;
    for (int i = hi-lo+1; i--; ++p)
        T *t = new(p, 0, 0) T;
}

template<class T> zEArray<T>::~zEArray()
{
    T *p = (T *) vec;
    if (!p) return;
    for (int i = hi-lo+1; i--; ++p)
        p->~T();
}

template<class T> void zEArray<T>::extend(int l, int h)
{
    T *t, *p;
    if (l > h) {
        handle("Inconsistent bounds",EINVAL);
        return;
    }
    if (l < lo) {
        realloc(l);
        p = (T *) init;
        for (int j = initcount; j--; ++p)
            t = new(p, 0, 0) T;
    }
    if (h > hi) {
        realloc(h);
        p = (T *) init;
        for (int j = initcount; j--; ++p)
            t = new(p, 0, 0) T;
    }
}
//#endif

template<class T> class zDArray : public _zdvec {
public:
    zDArray(int low = 0, int high = 0);
    ~zDArray();
    T &operator[](int i);
    void extend(int h, int l);
};

//#ifdef __zDArray_Expand_Template_Functions
template<class T> zDArray<T>::zDArray(int h, int l)
    : _zdvec(sizeof(T),h,l,(void *) 1)
{
    T *p = (T *) init;
    if (!p) return;
    for (int i = initcount; i--; ++p)
        T *t = new(p, 0, 0) T;
}

template<class T> zDArray<T>::~zDArray()
{
    T *p = (T *) vec;
    if (!p) return;
    for (int i = hi-lo+1; i--; ++p)
        p->~T();
}

template<class T> T &zDArray<T>::operator[](int i)
{
    T *t, *rv = (T *) get(i), *p = (T *) init;
    for (int j = initcount; j--; ++p)
        t = new(p, 0, 0) T;
    return *rv;
}

template<class T> void zDArray<T>::extend(int l, int h)
{
    T *t, *p;
    if (l > h) {
        handle("Inconsistent bounds",EINVAL);
        return;
    }
    if (l < lo) {
        realloc(l);
        p = (T *) init;
        for (int j = initcount; j--; ++p)
            t = new(p, 0, 0) T;
    }
    if (h > hi) {
        realloc(h);
        p = (T *) init;
        for (int j = initcount; j--; ++p)
            t = new(p, 0, 0) T;
    }
}
//#endif

template<class T> class zBDArray : public _zbdvec {
public:
    zBDArray(int low = 0, int high = 0, int batch = 32);
    ~zBDArray();
    T &operator[](int i);
    void extend(int h, int l);
};

//#ifdef __zBDArray_Expand_Template_Functions
template<class T> zBDArray<T>::zBDArray(int h, int l, int batch)
    : _zbdvec(sizeof(T),h,l,(void *) 1,batch)
{
    T *p = (T *) init;
    if (!p) return;
    for (int i = initcount; i--; ++p)
        T *t = new(p, 0, 0) T;
}

template<class T> zBDArray<T>::~zBDArray()
{
    T *p = (T *) vec;
    if (!p) return;
    for (int i = hi-lo+1; i--; ++p)
        p->~T();
}

template<class T> T &zBDArray<T>::operator[](int i)
{
    T *t, *rv = (T *) bget(i), *p = (T *) init;
    for (int j = initcount; j--; ++p)
        t = new(p, 0, 0) T;
    return *rv;
}

template<class T> void zBDArray<T>::extend(int l, int h)
{
    T *t, *p;
    if (l > h) {
        handle("Inconsistent bounds",EINVAL);
        return;
    }
    if (l < lo) {
        realloc(l);
        p = (T *) init;
        for (int j = initcount; j--; ++p)
            t = new(p, 0, 0) T;
    }
    if (h > hi) {
        realloc(h);
        p = (T *) init;
        for (int j = initcount; j--; ++p)
            t = new(p, 0, 0) T;
    }
}
//#endif




//////////////////////////////////////////////////////////////////////////////




#ifndef CHUNK
#define CHUNK 32
#endif

const int SVP = sizeof(void *);

class zAList : public zList, public zErrHandling {
	friend class zALCursor;

public:

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

	int currency() const { return _current; }

	int first() const { return count()? _current == 0: 1; }
	int last() const { return count()? (unsigned)_current == count()-1: 1; }

	void clear();

	void traverse(vf_t, void*);

	static int setchunk(int n) { int t = chunk; chunk = n; return t; }
	void dump(int contents = 0) const;

protected:
	zAList(dtorf_t, cleanup_behaviour);
	zAList(dtorf_t, void *, cleanup_behaviour);
	~zAList();

	void *insert(void *, zList::position);
	void *remove(zList::position);
	void *update(void *);

	void *setfirst()
		{ return count()? (_current = 0, body[0]): 0; }
	void *setlast()
		{ return count()? (_current = count()-1, body[_current]): 0; }
	void *move(int n);

	void *append(void *a) { return insert(a,listend); }
	void *prepend(void *a) { return insert(a,liststart); }

	void *head() const { return count()? body[0]: 0; }
	void *tail() const { return count()? body[count()-1]: 0; }

	void *gethead() { return remove(liststart); }
	void *gettail() { return remove(listend); }

	void *current() const { return count()? body[_current]: 0; }

	void merge(const zAList&);

	void *reset(int n = 0);

private:

	int sizeup();
	int sizedown();
	static chunk;

	void **body;
	int size, _current;
	static zErrHandler ceh;
};

template<class T> class zGAList: public zAList {
public:
	zGAList(cleanup_behaviour cb = zPtrColl::passive)
		: zAList((dtorf_t) dtf,cb) {}
	zGAList(T *a, cleanup_behaviour cb = zPtrColl::passive)
		: zAList((dtorf_t) dtf,a,cb) {}
	T *append(T *a) { return (T *) zAList::append(a); }
	T *prepend(T *a) { return (T *) zAList::prepend(a); }
	T *head() const { return (T *) zAList::head(); }
	T *tail() const { return (T *) zAList::tail(); }
	T *gethead() { return (T *) zAList::gethead(); }
	T *gettail() { return (T *) zAList::gettail(); }
	T *insert(T *a, zList::position rel = zList::before)
		{ return (T *) zAList::insert(a,rel); }
	T *remove(zList::position rel = zList::cur)
		{ return (T *) zAList::remove(rel); }
	T *update(T *a) { return (T *) zAList::update(a); }
	T *current() const { return (T *) zAList::current(); }
	T *operator()() const { return (T *) zAList::current(); }
	T *reset(int n = 0) { return (T *) zAList::reset(n); }
	T *setfirst() { return (T *) zAList::setfirst(); }
	T *setlast() { return (T *) zAList::setlast(); }
	T *next() { return (T *) move(1); }
	T *operator++() { return (T *) move(1); }
	T *operator++(int)
		{ T *t = (T *) zAList::current(); move(1); return t; }
	T *operator+=(int n) { return (T *) move(n); }
	T *prev() { return (T *) zAList::move(-1); }
	T *operator--() { return (T *) move(-1); }
	T *operator--(int)
		{ T *t = (T *) zAList::current(); move(-1); return t; }
	T *operator-=(int n) { return (T *) move(-n); }
	void traverse(void (*vf)(T*, void*), void *supplementary = 0)
		{ zAList::traverse((vf_t) vf, supplementary); }
	void merge(const zGAList<T> &a) { zAList::merge(a); }
private:
	static void dtf(T *);
	zGAList(const zGAList<T> &);
	zGAList<T> &operator=(const zGAList<T> &);
};

//#ifdef __zGAList_Expand_Template_Functions
template<class T> void zGAList<T>::dtf(T *p)
{
	p->~T();
}
//#endif



//////////////////////////////////////////////////////////////////////////////


const long SECONDS = 1;
const long MINUTES = SECONDS*60;
const long HOURS = MINUTES*60;
const long DAYS = HOURS*24;
#define SECSPERDAY DAYS


class zTimeInfo : public zErrHandling {
public:
    enum zTimeInfo_flags { not_us = 1, monthname = 2, dayname = 4,
         show_date = 8, show_time = 0x10, show_second = 0x20, hyphen = 0x40 };

    zTimeInfo();
                    // set all from system
    zTimeInfo(time_t);
                    // set from a long (seconds since 00:00:00 1/1/1970)
    zTimeInfo(const zTimeInfo&);
                    // copy constructor
    zTimeInfo(int, int, int = 0);
                    // set time - date from system
    zTimeInfo(const char *, int=0, int=0, int=0);
    zTimeInfo(int, int, int, int, int, int);
                    // set all from arguments
    ~zTimeInfo() { delete dbuf; delete tbuf; }


	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

    zTimeInfo &operator=(const zTimeInfo&);

// A set of access function return the values of the various members
// of the underlying struct tm.
    int sec() const { return ts.tm_sec; }
    int min() const { return ts.tm_min; }
    int hour() const {return ts.tm_hour; }
    int day() const { return ts.tm_mday; }
    int mon() const { return ts.tm_mon; }
    int year() const { return ts.tm_year; }
    int yday() const { return ts.tm_yday; }
    int dayw() const { return ts.tm_wday; }
    unsigned dayno() const
        { return last/SECSPERDAY; }

    operator long() const { return last; }

// The next group of functions provide character string representations
// of various aspects of the time and date.
    static unsigned flags(unsigned fv)
        { unsigned t = _flags; _flags = fv; return t; }
    static unsigned flags() { return _flags; }
    char *tod(int show_seconds = 0);
    char *wday();
    char *date()
        { return fdate(_flags); }
    char *dldate()          // like Tuesday April 9 1990
        { return fdate(show_date | monthname | dayname); }
    char *ldate()           // April 9 1990
        { return fdate(show_date | monthname); }
    char *sdate()           // 09/04/90
        { return fdate(show_date); }
    char *fdate(int);

// The set functions allows for an existing zTimeInfo object to be
// completely reset.
    time_t set(const char *, int = 0, int = 0, int = 0);
    time_t set(int, int , int , int = 0, int = 0, int = 0);
// The now function resets an existing zTimeInfo object from
// the system clock.
    time_t now();

// Date and time arithmetic operations deal in seconds.  SECONDS, MINUTES,
// HOURS and DAYS are defined as const long values above
    zTimeInfo operator+(long);
    zTimeInfo operator-(long);
    long operator-(const zTimeInfo &a)
        { return last - a.last; }
    zTimeInfo &operator+=(long);
    zTimeInfo &operator-=(long);

// It is also sometimes convenient to be able to adjust a date by
// months and years
    zTimeInfo nextmonth() const;
    zTimeInfo nextyear() const;
    zTimeInfo prevmonth() const;
    zTimeInfo prevyear() const;
    zTimeInfo &incmonth();
    zTimeInfo &incyear();
    zTimeInfo &decmonth();
    zTimeInfo &decyear();
    zTimeInfo &adjustby(int months, int years = 0);

    friend ostream &operator<<(ostream &, const zTimeInfo&);
    friend istream &operator>>(istream &, zTimeInfo&);

    static void UK() { _flags |= not_us; }
    static void US() { _flags &= ~not_us; }

private:
    int _set(const char *, int = 0, int = 0, int = 0);
    int daysin(int, int);
    int allocbuf(unsigned);
    static unsigned _flags;

    struct tm ts;           // as defined in TIME.H
    time_t last;
    char *dbuf, *tbuf;
	static zErrHandler ceh;
};


//////////////////////////////////////////////////////////////////////////////



class zBinTreeNode {
friend class zBinTree;
	zBinTreeNode* &ptr(int d) { return (d < 0)? left: right; }
	int leaf() { return !left && ! right; }
	static void reverse(zBinTreeNode * &a, zBinTreeNode* &b, int sense);

	zBinTreeNode *left, *right;
	void* body;
};

// In the course of building a tree it will be neccessary to make
// comparisons of whatever objects are to be stored in it.	Since
// we do not know at this stage what these will be, we define a type
// for a pointer to a user supplied function.
typedef int (* cmpf_t)(void *, void *);

class zBinTree : public zPtrColl, public zErrHandling {
public:
	enum order
		{ inorder = 1, revorder = 2, preorder = 4, postorder = 8 };
	enum direction { higher = +1, lower = -1 };


	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

	void clear() { cleanup(); root = 0; resetc(); }

	void draw(zBinTreeNode * = 0, int = 0, int = 0, int = 0) const;
	void dump(zBinTreeNode * = 0) const;  // works with int objects
protected:
// There is only one constructor. The first argument is required, and
// must point to a function suitable to destroy the objects in the tree.
// The second argument is also required and is to be used to compare the
// objects stored in the tree.  The third integer argument is defaulted
// to zero and is used to control the cleanup behaviour of the tree.
// If a non-zero value is supplied, the tree destructor will destroy
// the objects attached to the tree nodes as well as the nodes themselves.
	zBinTree(dtorf_t, cmpf_t comparison,
			zPtrColl::cleanup_behaviour = zPtrColl::passive);
	~zBinTree() { if (root && !leave()) cleanup(); }

	void *insert(void *);
	void *remove(void *);
	void *lookup(void*) const;
	void *seek(void *, direction = higher) const;
	void *min() const;
	void *max() const;
// The traverse function does a pass through the tree,	at each node
// the what_to_do function is called.  This can be used, for instance,
// to print out the contents of the tree in the order determined
// by the comparison function.	The order of visitation is as per
// enum order.
	void _trav(vf_t, void *, zBinTree::order, int) const;
// If code size is at a premium use _rtrav, the recursive version.
// This will however use up more stack space, and with a large degenerate
// tree may risk a stack overflow!
	void _rtrav(vf_t, void *, zBinTree::order, zBinTreeNode * = 0) const;

private:
	void cleanup();

	zBinTreeNode* root;
	cmpf_t cf;
	static zErrHandler ceh;
};

template<class T> class zGBinTree : public zBinTree {
public:
	zGBinTree(int (*f)(T*, T*), 
				zPtrColl::cleanup_behaviour cb = zPtrColl::passive)
		 : zBinTree((dtorf_t) dtf,(cmpf_t) f,cb) {}
	T *insert(T *a) { return (T *) zBinTree::insert(a); }
	T *remove(T *a) { return (T *) zBinTree::remove(a); }
	T *lookup(T *a) const { return (T *) zBinTree::lookup(a); }
	T *seek(T *a, direction r = zBinTree::higher) const
		{ return (T *) zBinTree::seek(a,r); }
	T *min() const { return (T *) zBinTree::min(); }
	T *max() const { return (T *) zBinTree::max(); }
	void traverse(void (*vf)(T*, void *), void *supplementary = 0,
					zBinTree::order o = inorder) const
		{ zBinTree::_trav((vf_t) vf,supplementary,o,(o == revorder)? +1: -1); }
	void r_traverse(void (*vf)(T*, void *), void *supplementary = 0,
					zBinTree::order o = inorder) const
		{ zBinTree::_rtrav((vf_t) vf,supplementary,o); }
private:
	static void dtf(T *);
	zGBinTree(const zGBinTree<T> &);
	zGBinTree<T> &operator=(const zGBinTree<T> &);
};

//#ifdef __zGBinTree_Expand_Template_Functions
template<class T> void zGBinTree<T>::dtf(T *p)
{
	p->~T();
}
//#endif


//////////////////////////////////////////////////////////////////////////////



class zTBinTreeNode {
friend class zTBinTree;

	enum zTBinTreeNode_flags
		{ lthread = 1, rthread = 2, tag = 4 };
	zTBinTreeNode* &ptr(int d) { return (d < 0)? left: right; }
	int leaf()
		{ return (flags & 3) == 3; }
	int thread(int d)
		{ return (d < 0)? (flags & lthread): (flags & rthread); }
	int tagged() { return flags & tag; }
	void setthread(int d)
		{ flags |= ((d < 0)? lthread: rthread); }
	void unsetthread(int d)
		{ flags &= ((d < 0)? ~lthread: ~rthread); }
	zTBinTreeNode *leftmost() const;
	zTBinTreeNode *rightmost() const;

	zTBinTreeNode *left, *right;
	void* body;
	unsigned short flags;
};

typedef int (* cmpf_t)(void *, void *);

class zTBinTree : public zPtrColl, public zErrHandling {

public:
	enum order
		{ inorder = 1, revorder = 2, preorder = 4, postorder = 8 };
	enum node_pointers { leftp = -1, rightp = 1 };
	enum direction { higher = +1, lower = -1 };

	static ehm_t class_error_mode(ehm_t em)
		{ return ceh.setmode(em); }

	void clear() { cleanup(); root = 0; resetc(); }

	void dump(zTBinTreeNode * = 0);	 // works with int objects
protected:
	zTBinTree(dtorf_t, cmpf_t comparison, cleanup_behaviour = zPtrColl::passive);
	~zTBinTree() { if (root && !leave()) cleanup(); }

	void *insert(void *);
	void *remove(void *);
	void *lookup(void*);
	void *seek(void *, zTBinTree::direction = higher);
	void *min();
	void *max();
	void *prev();
	void *next();
	void *current() const { return cp? cp->body: 0; }
	void _trav(vf_t, void *, zTBinTree::order, int) const;
	void r_traverse(vf_t vf, void *supplementary, zTBinTree::order o) const
		{ _rtrav(root, vf, supplementary, o); }

private:
	void _rtrav(zTBinTreeNode*, vf_t, void *, zTBinTree::order) const;
	void cleanup();
	static void reverse(zTBinTreeNode * &a, zTBinTreeNode* &b, int sense);

	zTBinTreeNode *root, *cp;
	cmpf_t cf;
	static zErrHandler ceh;
};

template<class T> class zGTBTree : public zTBinTree {
public:
	zGTBTree(int (*f)(T*, T*), cleanup_behaviour p = zPtrColl::passive)
		: zTBinTree((dtorf_t) dtf,(cmpf_t) f,p) {}
	T *insert(T *a) { return (T *) zTBinTree::insert(a); }
	T *remove(T *a) { return (T *) zTBinTree::remove(a); }
	T *lookup(T *a) { return (T *) zTBinTree::lookup(a); }
	T *seek(T *a, zTBinTree::direction r = zTBinTree::higher)
	 { return (T *) zTBinTree::seek(a,r); }
	T *min() { return (T *) zTBinTree::min(); }
	T *max() { return (T *) zTBinTree::max(); }
	T *prev() { return (T *) zTBinTree::prev(); }
	T *next() { return (T *) zTBinTree::next(); }
	T *operator()() const { return (T *) zTBinTree::current(); }
	void traverse(void (*vf)(T*, void*), void *supplementary = 0,
					zTBinTree::order o = inorder) const
		{ zTBinTree::_trav((vf_t) vf,supplementary,o,(o == revorder)? +1: -1); }
	void r_traverse(void (*vf)(T*, void*), void *supplementary = 0,
					zTBinTree::order o = inorder) const
		{ zTBinTree::r_traverse((vf_t) vf,supplementary,o); }
private:
	static void dtf(T *);
	zGTBTree(const zGTBTree<T> &);
	zGTBTree<T> &operator=(const zGTBTree<T> &);
};

//#ifdef __zGTBTree_Expand_Template_Functions
template<class T> void zGTBTree<T>::dtf(T *p)
{
	p->~T();
}
//#endif





#endif