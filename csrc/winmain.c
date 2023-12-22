#ifndef UNICODE
#define UNICODE
#endif 


#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

#include "GFXRECT.h"
#include "Point.h"
#include "List.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

GFXRECT* rectangles[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,};  

//RECT* prects[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,};  

PFXNODELIST recNodes = NULL;


char debugOut[1024];

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    //const wchar_t CLASS_NAME[]  = L"Sample Window Class";
	const wchar_t* CLASS_NAME  = L"Sample Window Class";
    
	OutputDebugStringA("wWinMain...\n");
	
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.
	OutputDebugStringA("CreateWindowEx...\n");

	recNodes = AllocList();


    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
	OutputDebugStringA("GetMessage...\n");
	
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

PFXPOINT RectToPoint(PGFXRECT r,int whichPoint)
{
	switch(whichPoint)
	{
	case 1:
		return AllocPoint(r->x,r->y);
	case 2:
		return AllocPoint(r->x + r->width,r->y);
	case 3:
		return AllocPoint(r->x + r->width,r->y + r->height);
	case 4:
		return AllocPoint(r->x,r->y + r->height);
	}
	return NULL;
}

BOOL IsOverlappedPoints(PFXPOINT l1, PFXPOINT r1, PFXPOINT l2, PFXPOINT r2) 
{ 
	// If one rectangle is on left side of other  
	if (l1->x >= r2->x || l2->x >= r1->x) 
	{ 
		return FALSE; 
	} 

	// If one rectangle is above other  
	if (l1->y >= r2->y || l2->y >= r1->y) 
	{ 
		return FALSE; 
	} 
	
	return TRUE; 
} 

BOOL IsOverlappedRects(PGFXRECT r1,PGFXRECT r2) 
{
	return IsOverlappedPoints(RectToPoint(r1,1), RectToPoint(r1,3), RectToPoint(r2,1), RectToPoint(r2,3)) ;
}


PFXNODELIST GetOverLappedRect(PGFXRECT r,PFXNODELIST objList)
{
	PFXNODELIST rects = AllocList();

	PFXNODE linkedlist = objList->head;

	// point it to old first node
	while(linkedlist->next != NULL)
	{
		PGFXRECT r2 = (PGFXRECT)(linkedlist->next->data);
		if(r!=r2 && IsOverlappedRects(r,r2))
		{
			ListAddStart(rects,r2);		
		}
		linkedlist = linkedlist->next;
	}
	return rects;
}


void PrintList(){
	struct node *p = head;
    //start from the beginning
   
	strcpy(debugOut,"[\n");
   
    while(p != NULL) 
	{
		//strcat(debugOut," %p ", p->data);
		//strcat(debugOut,"Name:");
		strcat(debugOut,((GFXRECT*)p->data)->name);
		strcat(debugOut,"\n");
		p = p->next;
    }
	
	strcat(debugOut,"]\n");
	
	OutputDebugStringA(debugOut);   
}

void DebugNode(struct node* p)
{
	GFXRECT* g = (GFXRECT*)p->data;
	
	sprintf(debugOut,"%s[%d]: %d %d %d %d\n",g->name,g->z,g->x,g->y,g->width,g->height);	
	OutputDebugStringA(debugOut);  
}

RECT* ToWinRECT(RECT* rect, GFXRECT* grect)
{
	rect->top = grect->y;
	rect->left = grect->x;
	rect->right = grect->x + grect->width;
	rect->bottom = grect->y + grect->height;	
	return rect;
}

GFXRECT* AddGRect(const char* name, int xPos, int yPos, int width, int height)
{
	OutputDebugStringA("AddGRect...\n");
	for(int i=0;i<10;i++)
	{
		if(!rectangles[i])
		{
			COLORREF c = RGB(0,0,255);
			
			if(i>3)
				c = RGB(255,0,0);
			if(i>5)
				c = RGB(130,90,44);
			

			rectangles[i] = AllocRect(name,xPos,yPos,width,height); 
			//rectangles[i] = new GRECT(NULL,xPos,yPos,width,height); 
			rectangles[i]->color = c;
			
			/*
			rectangles[i] = (GRECT*)malloc(sizeof(GRECT));
			memset(rectangles[i], 0, sizeof(GRECT));
			rectangles[i]->x = xPos;
			rectangles[i]->y = yPos;			
			rectangles[i]->width  = width;
			rectangles[i]->height = height;					
			rectangles[i]->color = c;				
			rectangles[i]->nextDepth;
			if(!name)
			{
				OutputDebugStringA("AddGRect::NO NAME");
				char* nname = (char*)malloc(64);
				sprintf(nname,"NAME:[%d]%p", rectangles[i]->color, (void*)rectangles[i]);
				//OutputDebugStringA(nname);
				//sprintf(nname,"BOB");
				rectangles[i]->name =(const char*)nname;
			}			
			else
			{
				OutputDebugStringA("AddGRect::HAS NAME ");
				OutputDebugStringA(rectangles[i]->name);
			    rectangles[i]->name = name;
			}
			*/
			OutputDebugStringA("AddGRect::ListAddStart...\n");
			ListAddStart(recNodes,rectangles[i]);
			//insertatbegin(rectangles[i]);
			
			//PrintList();
			VisitList(recNodes,DebugNode);
			
			return rectangles[i];
		}
	}	

	return NULL;
}

VOID DrawRectangles(HDC hdc)
{
	RECT target;

	for(int i=0;i<10;i++)
	{
		GFXRECT* p = rectangles[i];
		if(!p)
			break;

		FillRect(hdc, ToWinRECT(&target, p), CreateSolidBrush((COLORREF)p->color));			
	}
}

PGFXRECT GetSelectedRect(PFXNODELIST objList,int mx,int my)
{
	PGFXRECT highRect = NULL;
	
	OutputDebugStringA("GetSelectedRect::enter...\n");
	
	if(!objList)
		return NULL;
	
	PFXNODE p = objList->head;
	while(p != NULL)
	{
		PGFXRECT r = (PGFXRECT)(p->data);
		OutputDebugStringA("GetSelectedRect::got rect...\n");
		if(r->x < mx && (r->x + r->width) > mx)
		{
			if(r->y < my && (r->y + r->height) > my)
			{
				//System.out.println("Point in:" + r.name);
				if(highRect == NULL)
				{
					highRect = r;
				}
				else						
				{
					if(highRect->z < r->z)
						highRect = r;
				}
			}
		}	
		p = p->next;
	}
	
	OutputDebugStringA("GetSelectedRect::Exit...\n");
	
	return highRect;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            RECT small;  
            HDC hdc = BeginPaint(hwnd, &ps);

			sprintf(debugOut,"WM_PAINT top: %d left: %d bottom: %d right: %d\n", 
			        ps.rcPaint.top, ps.rcPaint.left, 
					ps.rcPaint.bottom, ps.rcPaint.right);
			OutputDebugStringA(debugOut);
			
            // All painting occurs here, between BeginPaint and EndPaint.
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

			

			DrawRectangles(hdc);
			
		
            /*
			small.top = 10;
	        small.left = 10;
            small.right = 100;
            small.bottom = 100;	    
            FillRect(hdc, &small, (HBRUSH) (COLOR_WINDOW+2));
			*/
			//Output("top: %d left: %d", ps.rcPaint.top, ps.rcPaint.left);
			
            EndPaint(hwnd, &ps);
        }
        return 0;
	case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			//sprintf(debugOut,"WM_MOUSEMOVE x: %d y: %d\n", 
			//       xPos, yPos);

			
			//OutputDebugStringA(debugOut);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			PGFXRECT hit = GetSelectedRect(recNodes,xPos,yPos);

			sprintf(debugOut,"WM_LBUTTONDOWN x: %d y: %d %p \n", 
			        xPos, yPos, hit);

			
			OutputDebugStringA(debugOut);
		}
		break;
	case WM_RBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			
			AddGRect(NULL, xPos, yPos, 100,100);
			/*
			for(int i=0;i<10;i++)
			{
				if(!prects[i])
				{
					prects[i] = (RECT*)malloc(sizeof(RECT));
					prects[i]->top = yPos;
					prects[i]->left = xPos;
					prects[i]->right = xPos + 100;
					prects[i]->bottom = yPos + 100;					
					break;
				}
			}
			*/			
			InvalidateRect(hwnd, NULL, TRUE);
			//UpdateWindow(hwnd);

			sprintf(debugOut,"WM_LBUTTONUP x: %d y: %d\n", 
			        xPos, yPos);

			
			OutputDebugStringA(debugOut);
		}
		break;
	case WM_NCMOUSELEAVE:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 

			sprintf(debugOut,"WM_NCMOUSELEAVE x: %d y: %d\n", 
			        xPos, yPos);

			
			OutputDebugStringA(debugOut);
		}
		break;

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
