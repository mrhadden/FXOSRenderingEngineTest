package com.foenix;

import java.awt.Color;
import java.awt.EventQueue;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import javax.swing.JPanel;

class Rectangles extends JPanel implements MouseMotionListener,MouseListener 
{
	static final Color palette[] = {   new Color(150, 150, 150),
									   new Color(128, 128, 255),
									   new Color(0, 150, 0),
									   new Color(150, 0, 0),
									   new Color(0, 0, 0),
									   new Color(255, 255, 255),
									   new Color(100, 100, 100)
									};
	
	List<RECT>       rects      = new ArrayList<RECT>();
	
	LinkedList<RECT> hitlist    = new LinkedList<RECT>();
	LinkedList<RECT> renderlist = new LinkedList<RECT>();
	LinkedList<RECT> interlist  = new LinkedList<RECT>();
	
	static RECT currentHover = null;
	static RECT currentFocus = null;
	
	public Rectangles()
	{
		RECT r;
		
		RECT.scaler = 5;
		
		addMouseListener(this);
		addMouseMotionListener(this);
		
		hitlist.add(new RECT("DESKTOP",0,0,65000,65000,0,1));
		
		r = new RECT("RECT1",30, 20, 50, 50);
		rects.add(r);
		hitlist.add(r);
		renderlist.add(r);
		setClientSize(r,2,2,2,2);
		setClientCenterOrigin(r);
			
		r = new RECT("RECT2",120, 20, 90, 60);
		rects.add(r);
		hitlist.add(r);
		renderlist.add(r);
		
		r = new RECT("RECT3",140, 30, 100, 75,-1,2);
		rects.add(r);
		hitlist.add(r);		
		renderlist.add(r);
		setClientSize(r,5,15,5,5);
		setClientOrigin(r,100,100);
		
		r = new RECT("RECT4",200, 20, 100, 200);
		rects.add(r);
		hitlist.add(r);		
		renderlist.add(r);	

		r = new RECT("Menubar",0, 0, 1580, 16,-1,2);
		rects.add(r);
		hitlist.add(r);		
		renderlist.add(r);			
		
		for(int i=0;i<10;i++)
		{
			r = new RECT("MENU" + i,0, 20 + (20*i), 50, 20,-1,2 | 4);
			rects.add(r);
			hitlist.add(r);		
			renderlist.add(r);	
		}
		
		RECT.scaler = 1;
	}

	private void setClientSize(RECT r,int i,int j,int k,int l)
	{
		r.clientRect = new RECT(r.name + "-child",
				                r.x/RECT.scaler+(i),
				                r.y/RECT.scaler+(j),
				                r.width/RECT.scaler - ((k + i)),
				                r.height/RECT.scaler - ((l + j)));
		
	}

	private RECT getSelectedRect(LinkedList objList,int mx,int my)
	{
		RECT highRect = null;
		
		for(RECT r : hitlist)
		{
			if(r.x < mx && (r.x + r.width) > mx)
			{
				if(r.y < my && (r.y + r.height) > my)
				{
					//System.out.println("Point in:" + r.name);
					if(highRect == null)
					{
						highRect = r;
					}
					else						
					{
						if(highRect.z < r.z)
							highRect = r;
					}
				}
			}	
		}
		return highRect;
	}


	
	private Point rectToPoint(RECT r,int whichPoint)
	{
		switch(whichPoint)
		{
		case 1:
			return new Point(r.x,r.y);
		case 2:
			return new Point(r.x + r.width,r.y);
		case 3:
			return new Point(r.x + r.width,r.y + r.height);
		case 4:
			return new Point(r.x,r.y + r.height);
		}
		return null;
	}
	
	private List<RECT> getOverLappedRect(RECT r,List<RECT> objList)
	{
		List<RECT> rects = new ArrayList<RECT>();
		
		for(RECT r2 : objList)
		{
			if(r!=r2 && isOverlappedRects(r,r2))
				rects.add(r2);
		}
		
		return rects;
	}
	
	private RECT intersection( RECT r, RECT rhs )
    {
		if(r == null || rhs == null)
			return null;
		
      RECTP   rectTemp = new RECTP();

      RECTP rp   = RECTP.toRECTP(r);
      RECTP rhsp = RECTP.toRECTP(rhs);
      
      rectTemp.topLeft.x       = Math.max( rhsp.topLeft.x, rp.topLeft.x );
      rectTemp.bottomRight.x   = Math.min( rhsp.bottomRight.x, rp.bottomRight.x );
      rectTemp.topLeft.y       = Math.max( rhsp.topLeft.y, rp.topLeft.y );
      rectTemp.bottomRight.y   = Math.min( rhsp.bottomRight.y, rp.bottomRight.y );
      

      if ( rectTemp.topLeft.x > rectTemp.bottomRight.x )
      {
    	 return null;
      }
      if ( rectTemp.topLeft.y > rectTemp.bottomRight.y )
      {
        return null;
      }

      return rectTemp.toRECT("With" + rhs.name);
    }	
	
	private boolean isOverlappedRects(RECT r1,RECT r2) 
	{
		return isOverlappedRects(rectToPoint(r1,1), rectToPoint(r1,3), rectToPoint(r2,1), rectToPoint(r2,3)) ;
	}
	
	private boolean isOverlappedRects(Point l1, Point r1, Point l2, Point r2) 
	{ 
        // If one rectangle is on left side of other  
        if (l1.x >= r2.x || l2.x >= r1.x) { 
            return false; 
        } 
  
        // If one rectangle is above other  
        if (l1.y >= r2.y || l2.y >= r1.y) { 
            return false; 
        } 
        
        return true; 
    } 
	
	
	public void mouseMoved(MouseEvent e)
	{
		int mx = e.getX();
		int my = e.getY();
		RECT selectedRect = null;
		
		//System.out.println("Mouse Moved:" + e.getX() + ":" + e.getY());
		selectedRect = getSelectedRect(hitlist,mx,my);
		if(selectedRect!=null)
		{
			//System.out.println("Point in:" + highhit.name);
			if(currentHover!=selectedRect)
			{
				if(currentHover!=null)
				{
					System.out.println("FX_MOUSE_EXIT: " + currentHover.name + " @ [" + currentHover.z + "]");
					if((currentHover.attr & 2) == 2)
					{
						System.out.println(currentHover.name + " was special ");
						if(currentHover!=currentFocus)
						{
							currentHover.color = 0;
							repaint();
						}
					}
				}
				
				currentHover = selectedRect;
				System.out.println("FX_MOUSE_ENTER: " + currentHover.name + " @ [" + currentHover.z + "]");
				
				if((currentHover.attr & 2) == 2)
				{
					System.out.println(currentHover.name + " is special ");
					if(currentHover!=currentFocus)
					{
						currentHover.color = 2;
						repaint();
					}
				}
			}
		}

	}

	@Override
	public void mouseClicked(MouseEvent e)
	{
		int mx = e.getX();
		int my = e.getY();
		RECT highhit = null;
		
		highhit = getSelectedRect(hitlist,mx,my);
		if(highhit!=null && currentFocus!=highhit && (highhit.attr & 1) == 0)
		{
			if(currentFocus!=null && currentFocus!=highhit)
			{
				currentFocus.color = 0;
				System.out.println("FX_LOST_FOCUS: " + currentFocus.name);
			}
			
			highhit.color = RGB(128,128,128);
			//highhit.z = RECT.nextDepth++;
			
			//renderlist.remove(highhit);
			//renderlist.add(highhit);
			
			currentFocus = highhit;
			
			System.out.println("FX_GOT_FOCUS: " +  currentFocus.name);
			
			List<RECT> overlaps = getOverLappedRect(currentFocus,hitlist);
			if(overlaps!=null && overlaps.size() > 0)
			{
				for(RECT ol : overlaps)
				{
					if(!ol.name.equalsIgnoreCase("desktop"))
					{
						System.out.println("\tOverlaps: " +  ol.name);
						RECT ri = intersection(currentFocus,ol);
						if(ri!=null)
						{
							interlist.add(ri);
							/*
							System.out.println("\tIntersect:name: " +  ri.name);
							System.out.println("\tIntersect:x: " +  ri.x);
							System.out.println("\tIntersect:y: " +  ri.y);
							System.out.println("\tIntersect:w: " +  ri.width);
							System.out.println("\tIntersect:h: " +  ri.height);
							*/
						}
					}
				}
			}
			
			repaint();			
		}
		else if(highhit!=null && currentFocus==highhit)
		{
			System.out.println(highhit.name + " STILL HAS FOCUS");
		}
	}

	@Override
	public void mouseEntered(MouseEvent arg0)
	{
		//System.out.println("Mouse entered:");
	}

	@Override
	public void mouseExited(MouseEvent arg0)
	{
		//System.out.println("Mouse exited:");
		
	}

	@Override
	public void mousePressed(MouseEvent arg0)
	{
		//System.out.println("Mouse pressed:");
	}

	@Override
	public void mouseReleased(MouseEvent arg0)
	{
		//System.out.println("Mouse released:");
	}
	
	public void mouseDragged(MouseEvent e)
	{
		System.out.println("Mouse Dragged:" + e.getX() + ":" + e.getY());
	}

	//static final int scaler = 5;
	
	private void doDrawing(Graphics g)
	{
		System.out.println("doDrawing()");
		Graphics2D g2d = (Graphics2D) g;

		RenderingHints rh = new RenderingHints(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		rh.put(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
		g2d.setRenderingHints(rh);

		this.setBackground(Color.CYAN);
		
		for(RECT r : renderlist)
		{
			g2d.setPaint(palette[r.color]);
			g2d.fillRect(r.x,r.y,r.width,r.height);
			g2d.setPaint(palette[4]);
			g2d.drawRect(r.x,r.y,r.width,r.height);
			
			clientDrawText(g2d,r,2,0,r.name);
			
			if(r.clientRect!=null)
			{
				g2d.setPaint(palette[5]);
				g2d.drawRect(r.clientRect.x,r.clientRect.y,r.clientRect.width,r.clientRect.height);
				clientDrawLine( g2d, r,0,0,100,100);				
				clientDrawLine( g2d, r,0,0,-100,100);
			}
			
			
		}
		
		if(interlist!=null && interlist.size() > 0)
		{
			for(RECT r : interlist)
			{
				g2d.setPaint(palette[5]);
				g2d.drawRect(r.x,r.y,r.width,r.height);
				//g2d.fillRect(r.x,r.y,r.width,r.height);
			}
			interlist.clear();
		}
		
		
	}

	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		doDrawing(g);
	}

	private void clientDrawText(Graphics2D g2d,RECT r,int x,int y,String text)
	{
		g2d.setPaint(palette[4]);
		FontMetrics fm = g2d.getFontMetrics();
		g2d.drawString(text, (r.x + x) , (r.y + fm.getHeight()+ y));	
	}
	
	
	
	private void clientDrawLine(Graphics2D g2d,RECT r,int x,int y,int xp,int yp)
	{
		if(g2d!=null && r.clientRect!=null)
		{
			g2d.drawLine(r.clientRect.x + x + r.clientRect.orgX, 
					     r.clientRect.y + y + r.clientRect.orgY, 
					     r.clientRect.x + xp + r.clientRect.orgX, 
					     r.clientRect.y + yp + r.clientRect.orgY);
		}
	}

	private void setClientCenterOrigin(RECT r)
	{
		if(r.clientRect!=null)
		{ 
			setClientOrigin(r,r.clientRect.width /2,
					          r.clientRect.height/2);
		}
	}
	
	private void setClientOrigin(RECT r,int x,int y)
	{
		if(r.clientRect!=null)
		{
			r.clientRect.orgX = x;
			r.clientRect.orgY = y;
		}
	}
}
