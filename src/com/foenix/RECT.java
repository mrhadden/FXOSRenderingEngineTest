package com.foenix;

public class RECT
{
	static public long nextDepth = 1;
	
	public static int scaler = 1;
	
		
	public RECT(String name, int x,int y,int width,int height)
	{
		this( name, x, y, width, height,-1,0);
	}
	
	public RECT(String name, int x,int y,int width,int height,long z,int attr)
	{
		//System.out.println("z:" + z);
		this.name = name;
		this.x = x * scaler;
		this.y = y * scaler;
		this.width = width * scaler;
		this.height = height * scaler;
		if(z == -1)
			this.z = nextDepth++;
		else
			this.z = z;
		
		this.color = 0;
		this.attr = attr;
	}
	
	public String name;
	public int x;
	public int y;
	public int width;
	public int height;
	public long z;
	public int color ;
	public int attr;

	public int orgX = 0;
	public int orgY = 0;
	
	public RECT clientRect;
}
