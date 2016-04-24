#pragma once
#include <math.h>

namespace graphics
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	class TObject
	{
	protected:
		bool Visible, Active;
	public:
		TObject():Visible(false),Active(false){};
		virtual void Show(Graphics ^g)=0;
		virtual void Hide(Graphics ^g)=0;
		virtual void Move(Graphics ^g,int dx,int dy)=0;
		virtual int GetX(Graphics ^g)=0;
		virtual int GetY(Graphics ^g)=0;
	};

	class TPoint: public TObject
	{
	protected:
		int x,y;
	public:
		TPoint(int _x1=0,int _y1=0)//:x(_x1),y(_y1)
		{
			x=_x1;
			y=_y1;
			Visible = false;
			Active = false;
		}
		virtual void Show(Graphics ^g)
		{
			g->DrawEllipse(Pens::Black,x-2,y-2,4,4);
			Visible=true;
			Active=true;
		}
		virtual void Hide(Graphics ^g)
		{
			g->DrawEllipse(Pens::White,x-2,y-2,4,4);
			Visible=false;
			Active=false;
		}
		virtual void Move(Graphics ^g,int dx, int dy)
		{
			Hide(g);
			x += dx;
			y += dy;
			Show(g);
		}
		virtual int GetX(Graphics ^g){return x;}
		virtual int GetY(Graphics ^g){return y;}
	};
}