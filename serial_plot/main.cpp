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
#define SERIAL_BUFFER_MULT 32
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
    bool static shift_gui_buffer = false;
    int static gui_buf_step = 0;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (DKGRAY_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc); 

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "Serial Plot", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE |WS_MINIMIZEBOX| WS_MAXIMIZEBOX,
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
			glPushMatrix ();
			glColor3d(3,1,0.2);
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
			
			
			glBegin(GL_LINE_STRIP);
			for (t=-0.01;t<=0.01;t+=0.005) { 
			 
				glVertex2d(t,0.5);
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
			glColor3d(1,1,1);
			glBegin(GL_LINES);
					 
				if(consSer->getCurrBuffNum() != currentRxBuffUart){
					currentRxBuffUart = consSer->getCurrBuffNum();
					gui_buf_step++;
					shift_gui_buffer = true;
					if(SERIAL_BUFFER_MULT == gui_buf_step){
						gui_buf_step = 0;
					}
				}
				
				
//				for(int j = 0; SERIAL_BUFFER_MAX_SIZE > j; j++){
//					gui_buff[j+SERIAL_BUFFER_MAX_SIZE*gui_buf_step] = consSer->getRxData()[j]/255.0;
//				}
				
				for(int j = 0; SERIAL_BUFFER_MAX_SIZE > j; j++){
 					gui_buff[(GUI_BUFF_SZ -1) -(j +SERIAL_BUFFER_MAX_SIZE*gui_buf_step)] = consSer->getRxData()[j]/255.0;
 				}
				
				/*shift left the gui buffer.*/
				if(true == shift_gui_buffer ){
					
					
//					shift_gui_buffer = false;
//					for(int j = 0; SERIAL_BUFFER_MAX_SIZE > j; j++){
//						for(int i = 1; GUI_BUFF_SZ > i; i++){
//					 		gui_buff[i - 1] = gui_buff[i];
//					 		
//						}
//						gui_buff[GUI_BUFF_SZ - 1] = 0;
//					}
					
				}
    
				for (int i =0; GUI_BUFF_SZ > i ;i++) {
			
			 		glVertex2d((i/100.0 ) -1.0  ,gui_buff[i]);
					  
				}    
			
			glEnd();         
			glPopMatrix ();     
			SwapBuffers (hDC);  
			theta += .01f;
			Sleep (1);  
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
