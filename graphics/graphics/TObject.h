#pragma once
#include "list.h"
#include <math.h>

namespace graphics
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	struct TPoint
	{
		int x,y;
		TPoint(int _x = 0, int _y = 0) : x(_x),y(_y) {}
	};

	class TShape
	{
	protected:
		bool Visible, Active;
	public:
		TShape():Visible(false),Active(false){};
		virtual TPoint Show(Graphics ^g)=0;
		virtual TPoint Hide(Graphics ^g)=0;
		//virtual void Move(Graphics ^g,int dx,int dy)=0;
		//virtual int GetX(Graphics ^g)=0;
		//virtual int GetY(Graphics ^g)=0;
	};

	class TShapePoint : public TShape
	{
		TPoint *p;
	public:
		TShapePoint (TPoint *_p) : p(_p) {}
		TPoint Show(Graphics ^g)
		{
			g->DrawEllipse(Pens::Black,p->x-2,p->y-2,4,4);
			Visible=true;
			Active=true;
			return *p;
		}
		TPoint Hide(Graphics ^g)
		{
			g->DrawEllipse(Pens::White,p->x-2,p->y-2,4,4);
			Visible=false;
			Active=false;
			return *p;
		}
	};

	class TShapeLine : public TShape
	{
		TShape *l, *r;
	public:
		TShapeLine (TShape *_l, TShape *_r) : l(_l), r(_r) {}
		TPoint Show (Graphics ^g)
		{
			TPoint rp, lp;
			rp = r->Hide(g);
			lp = l->Hide(g);
			g->DrawLine(Pens::Black, rp.x, rp.y, lp.x, lp.y);
			Active = true;
			Visible = true;
			return lp;
		}
		TPoint Hide (Graphics ^g)
		{
			TPoint rp, lp;
			rp = r->Hide(g);
			l->Hide(g);
			g->DrawLine(Pens::White, rp.x, rp.y, lp.x, lp.y);
			Active = false;
			Visible = false;
			return lp;
		}
	};

	class TRectangle: public TShape
	{
	protected:
		TShape *l, *r;
	public:
		TRectangle(TShape *_l, TShape *_r):l(_l),r(_r) {}
		TPoint Show(Graphics ^g)
		{
			TPoint rp, lp;
			rp = r->Hide(g);
			lp = l->Hide(g);
			g->DrawRectangle(Pens::Black,Math::Min(rp.x,lp.x),Math::Min(rp.y,lp.y),abs(rp.x-lp.x),abs(rp.y-lp.y));
			Active = true;
			Visible = true;
			return lp;
		}
		TPoint Hide(Graphics ^g)
		{
			TPoint rp, lp;
			rp = r->Hide(g);
			lp = l->Hide(g);
			g->DrawRectangle(Pens::White,Math::Min(rp.x,lp.x),Math::Min(rp.y,lp.y),abs(rp.x-lp.x),abs(rp.y-lp.y));
			Active = false;
			Visible = false;
			return lp;
		}
	};

	class TEllipse: public TShape
	{
	protected:
		TShape *l, *r;
	public:
		TEllipse(TShape *_l, TShape *_r):l(_l),r(_r) {}
		TPoint Show(Graphics ^g)
		{
			TPoint rp, lp;
			rp = r->Hide(g);
			lp = l->Hide(g);
			g->DrawEllipse(Pens::Black,Math::Min(rp.x,lp.x),Math::Min(rp.y,lp.y),abs(rp.x-lp.x),abs(rp.y-lp.y));
			Visible=true;
			Active=true;
			return lp;
		}
		TPoint Hide(Graphics ^g)
		{
			TPoint rp, lp;
			rp = r->Hide(g);
			lp = l->Hide(g);
			g->DrawEllipse(Pens::White,Math::Min(rp.x,lp.x),Math::Min(rp.y,lp.y),abs(rp.x-lp.x),abs(rp.y-lp.y));
			Visible=false;
			Active=false;
			return lp;
		}
	};

	class TGroup :public TShape
	{
	protected:
		TList<TShape*> List;
	public:
		void InsertUnit(TShape *unit)
		{
			List.AddFirst(unit);
		}
		TPoint Show(Graphics ^g)
		{
			for (List.Reset(); !List.IsEnd(); List.GoNext())
			{
				List.GetCurrentVal()->Show(g);
			}
			Active = true;
			Visible = true;
		}
		TPoint Hide(Graphics ^g)
		{
			for (List.Reset(); !List.IsEnd(); List.GoNext())
			{
				List.GetCurrentVal()->Hide(g);
			}
			Visible=false;
			Active=false;
		}
	};


}