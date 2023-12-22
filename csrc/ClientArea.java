package com.foenix;

public class ClientArea extends RECT
{
	public RECT parent;
	
	public ClientArea(RECT parent, String name,int x,int y,int width,int height)
	{
		super(parent+"-child", x, y, width, height);
		this.parent = parent;
	}
}
