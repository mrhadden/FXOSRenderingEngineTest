package com.foenix;

public class RECTP
{
	public Point topLeft = new Point(0,0);
	public Point bottomRight = new Point(0,0);
	
	public RECTP(int left,int top, int right,int bottom)
	{
		topLeft.x = left;
		topLeft.y = top;
		
		bottomRight.x = right;
		bottomRight.y = bottom;		
	}
	
	public RECTP()
	{
		// TODO Auto-generated constructor stub
	}

	public RECT toRECT(String name)
	{
		return new RECT(name,topLeft.x,topLeft.y,bottomRight.x - topLeft.x,bottomRight.y - topLeft.y);
	}
	
	static public RECTP toRECTP(RECT r)
	{
		return new RECTP(r.x,r.y,r.x + r.width,r.y+r.height);
	}
}
