/**************************
 * Includes
 *
 **************************/
#include "main.hpp"		
static uint8_t gSerialBuffer[SERIAL_BUFFER_MAX_SIZE];


/**************************
 * Function Declarations
 *
 **************************/
// 
//
//
//void * serial_task(void * p){
//	while(1){
//		read_serial_resp(gSerialBuffer);
//	}
//}

 

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);


double func_test(double x);

double func_test(double x)
{
   //	read_serial_resp(gSerialBuffer);
    return 0.25*sin(10*(x));//*cos(300*x);
    //return   gSerialBuffer[(int)x]/255.0;
}

/*rx cyclic serial buffer*/
uint8_t RxCBf1[RX_SER_BUF_MAX_SZ];
uint8_t RxCBf2[RX_SER_BUF_MAX_SZ];

//test1
#define SERIAL_BUFFER_MULT 16
#define GUI_BUFF_SZ SERIAL_BUFFER_MAX_SIZE*SERIAL_BUFFER_MULT
float gui_buff[GUI_BUFF_SZ];
//etest1


/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;
    uint8_t currentRxBuffUart = 0;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc); 

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "OpenGL Sample", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 5*256, 4*256,
      NULL, NULL, hInstance, NULL);
      
      
      
      
    /*console*/   
    AllocConsole(); 

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((intptr_t) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((intptr_t) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;
      
      
      
       

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);
    
    /*enable serial*/
    string comPort = "COM8";
	init_serial(comPort);
	
	wqueue<uint8_t>  queue;
	SerialProduserThread * prodSer = new SerialProduserThread(queue);
	SerialConsumerThread * consSer = new SerialConsumerThread(queue,RxCBf1,RxCBf2);
	prodSer->start();
	consSer->start();
	printf("hi");
 	 
	 
	currentRxBuffUart = consSer->getCurrBuffNum();
    /* program main loop */
    while (!bQuit)
    { 
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        { 
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else  
        {
            /* OpenGL animation code goes here */

//            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
//            glClear (GL_COLOR_BUFFER_BIT);
//
//            glPushMatrix ();
//            glRotatef (theta, 0.0f, 0.0f, 1.0f);
//            glBegin (GL_TRIANGLES);
//            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (0.0f, 1.0f);
//            glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (0.108f, -0.5f);
//            glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (-0.87f, -0.5f);
//            glEnd ();
//            glPopMatrix ();
//
//            SwapBuffers (hDC);
//
//            theta += 1.0f;
			
			glPushMatrix ();
			//glRotatef (theta, 0.0f, 0.0f, 1.0f);
			double t;
			 
			
			//draw x 
			glClear (GL_COLOR_BUFFER_BIT);
			glBegin(GL_LINE_STRIP);
			
			for (t=T_MIN;t<=T_MAX;t+=T_PRECISION) {
				glVertex2d(t,0);
			//glVertex2d(func_test(t),t);
			}
			glEnd();
			
			//draw y
			
			glBegin(GL_LINE_STRIP);
			
				for (t=T_MIN;t<=T_MAX;t+=T_PRECISION) {
				glVertex2d(0,t);
				//glVertex2d(func_test(t),t); 
			}
			glEnd();
			
			
			//draws the graph 
			glBegin(GL_LINE_STRIP);
			 
//			for (t=T_MIN;t<=T_MAX;t+=T_PRECISION) {
//				//glVertex2d(t,func_test(t-theta)); 
//				//glVertex2d(func_test(t),t);
//			}   

			 
//			for (int i =0; i<=((SERIAL_BUFFER_MAX_SIZE + 1)/2 );i++) {
//			
//			 	glVertex2d((i/100.0 ) -1.0 ,consSer->getRxData()[i]/255.0);
//					  
//			} 
//			
//			static int one_shot = 1;
//			if(one_shot){
//				one_shot = 0;
//				for (int i = 1 + (SERIAL_BUFFER_MAX_SIZE + 1)/2; i<=SERIAL_BUFFER_MAX_SIZE ;i++) {
//				
//				 	glVertex2d((i/100.0 ) -1.0 ,consSer->getRxData()[i]/255.0);
//						  
//				} 
//			}
		
				
				int static gui_buf_step = 1;
				
				if(consSer->getCurrBuffNum() != currentRxBuffUart){
					gui_buf_step++;
					if(SERIAL_BUFFER_MULT == gui_buf_step){
						gui_buf_step = 1;
					}
				}
				for(int j = 0; j < SERIAL_BUFFER_MAX_SIZE; j++){
				
					//gui_buff[j] = consSer->getRxData()[j]/255.0;
					gui_buff[j+SERIAL_BUFFER_MAX_SIZE*gui_buf_step] = consSer->getRxData()[j]/255.0;
					
				}
  
				for (int i =0; i<= GUI_BUFF_SZ ;i++) {
			
			 		glVertex2d((i/100.0 ) -1.1  ,gui_buff[i]);
					  
				}  
			 
			
			
			glEnd();         
			glPopMatrix ();     
			SwapBuffers (hDC);  
			theta += .01f;
			Sleep (10);  
        } 
    } 

    /* shutdown OpenGL */ 
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure 
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/ 

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}