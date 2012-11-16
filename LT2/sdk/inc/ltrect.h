
#ifndef __LTRECT_H__
#define __LTRECT_H__


	class LTRect
	{
	public:
		LTRect(int l=0, int t=0, int r=0, int b=0) : left(l), top(t), right(r), bottom(b) {}
		inline void	Init(int inLeft, int inTop, int inRight, int inBottom)
		{
			left = inLeft;
			top = inTop;
			right = inRight;
			bottom = inBottom;
		}

		int left, top, right, bottom;
	};

#endif  // __LTRECT_H__


