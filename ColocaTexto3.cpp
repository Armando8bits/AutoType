/* INICIO 28 FEBRERO 2023 - TERMINADO EL 2 DE MARZO DE 2023 POR ROQUE ARMANDO RAMIREZ P
LO QUERIA HACER EN C++ COMO DESAFIO PERSONAL Y PARA TENER UN MEJOR RENDIMIENTO YA QUE EL DE PYTHON ERA BUENO PERO,
NO PODIA COPIAR PALABRAS CON ACENTOS Y CARACTERES ESPECIALES, ADEMAS QUE PARA INICARLO, TENIA QUE EJECUTAR EL INTERPRETE
Y ESO ME QUITABA TIEMPO.
ESTE PROYECTO PUEDE SER MEJOR SU EN LUGAR DE OBTENER EL ASCCI DE CADA CARACTER, OPTIENE DIRECTAMENTE EL HEX

Codigo de ventana sacado de: https://www.codigazo.com/en-c/codigo-ejemplo-crear-ventana-en-c
ayuda para las claves de las teclas: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
Ayuda verificando codigos hex y ascii: https://bytetool.web.app/en/ascii/
ayudas para completar el proyecto: https://batchloaf.wordpress.com/2014/10/02/using-sendinput-to-type-unicode-characters/
                                https://batchloaf.wordpress.com/2012/10/18/simulating-a-ctrl-v-keystroke-in-win32-c-or-c-using-sendinput/
                                https://batchloaf.wordpress.com/2012/04/17/simulating-a-keystroke-in-win32-c-or-c-using-sendinput/


 */

#define _WIN32_WINNT 0x0500 // Es necesaria esta definicion para esconder ventana de consola
#include <windows.h>        // Libreria que contiene las funciones de Winapi
#include <vector>           // Para utilizar std::vector
// #include <cstdio>
//  #include <string>
//  #include <wchar.h>
//  #include <iostream>

// declaraciones de controles con eventos:
#define Btn1 101 // boton Tipear
#define Btn2 102 // boton Limpiar
#define Btn3 103 // boton copiar
#define Btn4 104 // boton pegar
#define ID_EDIT1 105
#define ID_LINK 106 // label de mi nombre que abre link a Github

HWND CmdTipear;
HWND CmdLimpiar;
HWND CmdCopiar;
HWND CmdPegar;
HWND TxtcajaTexto;
HWND LblLink; // label de mi nombre que abre link a Github

void TipeaTexto(wchar_t *Caracter, int Largo);
void EjecutarHotKey(int Tecla1, int Tecla2);

/*  Declaracion del procedimiento de windows  */

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Declaramos una variable de tipo char para guardar el nombre de nuestra aplicacion  */

char NombreClase[] = "Estilos";

HWND ventana1;       /* Manejador de la ventana*/
MSG mensajecomunica; /* Mensajes internos que se envian a la aplicacion */
WNDCLASSEX estilo1;  /* Nombre de la clase para los estilos de ventana */

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow)

{
    /* Creamos la estructura de la ventana indicando varias caracteristicas */
    estilo1.hInstance = hThisInstance;
    estilo1.lpszClassName = NombreClase;
    estilo1.lpfnWndProc = WindowProcedure;
    estilo1.style = CS_DBLCLKS;
    estilo1.cbSize = sizeof(WNDCLASSEX);
    estilo1.hIcon = LoadIcon(NULL, IDI_QUESTION);
    estilo1.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
    estilo1.hCursor = LoadCursor(NULL, IDC_ARROW);
    estilo1.lpszMenuName = NULL; /* Sin Menu */
    estilo1.cbClsExtra = 0;
    estilo1.cbWndExtra = 0;
    estilo1.hbrBackground = (HBRUSH)COLOR_WINDOW; /* Color del fondo de ventana */

    /* Registramos la clase de la ventana */

    if (!RegisterClassEx(&estilo1))

        return 0;

    /* Ahora creamos la ventana a partir de la clase anterior */

    ventana1 = CreateWindowEx(
        0,
        NombreClase,                              /* Nombre de la clase */
        ("Coloca Texto V3.0"),                    /* Titulo de la ventana */
        WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, /* Ventana por defecto para que no sea redimencioanda */
        400,                                      /* Posicion de la ventana en el eje X (de izquierda a derecha) */
        70,                                       /* Posicion de la ventana, eje Y (arriba abajo) */
        310,                                      /* Ancho de la ventana */
        340,                                      /* Alto de la ventana */
        HWND_DESKTOP,
        NULL, /* Sin menu */
        hThisInstance,
        NULL);

    // CREA LOS LABELS QUE NO SE MODIFICAN:
    CreateWindowW(L"Static", L"Copie el texto a Tipear Aquí:", WS_VISIBLE | WS_CHILD | ES_LEFT, 55, 5, 200, 20, ventana1, 0, 0, 0);
    LblLink = CreateWindowW(L"Static", L"Creado por: Armando Ramírez", WS_VISIBLE | WS_CHILD | ES_LEFT | SS_NOTIFY, 55, 285, 200, 20, ventana1, (HMENU)ID_LINK, 0, 0);
    SetClassLongPtr(LblLink, GCLP_HCURSOR, (LONG_PTR)LoadCursor(NULL, IDC_HAND)); // Establecer el cursor del ratón como mano al pasar sobre el label
                                                                                  // crea el textBox
    TxtcajaTexto = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 0, 25, 300, 220, ventana1, (HMENU)ID_EDIT1, 0, 0);
    // creamos botones
    CmdTipear = CreateWindowEx(0, "button", "Tipear Texto", WS_VISIBLE | WS_CHILD | 0, 5, 250, 100, 25, ventana1, (HMENU)Btn1, 0, 0);
    CmdLimpiar = CreateWindowEx(0, "button", "Limpiar", WS_VISIBLE | WS_CHILD | 0, 106, 250, 60, 25, ventana1, (HMENU)Btn2, 0, 0);
    CmdCopiar = CreateWindowEx(0, "button", "Copiar", WS_VISIBLE | WS_CHILD | 0, 167, 250, 60, 25, ventana1, (HMENU)Btn3, 0, 0);
    CmdPegar = CreateWindowEx(0, "button", "Pegar", WS_VISIBLE | WS_CHILD | 0, 228, 250, 60, 25, ventana1, (HMENU)Btn4, 0, 0);

    /* Hacemos que la ventana sea visible */

    ShowWindow(ventana1, nCmdShow);
    ShowWindow(GetConsoleWindow(), SW_HIDE); // Funcion para esconder la ventana de consola
    /* Hacemos que la ventan se ejecute hasta que se obtenga resturn 0 */

    while (GetMessage(&mensajecomunica, NULL, 0, 0))
    {
        /* Traduce mensajes virtual-key */
        TranslateMessage(&mensajecomunica);
        /* Envia mensajes a WindowProcedure */
        DispatchMessage(&mensajecomunica);
    }
    return mensajecomunica.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND ventana1, UINT mensajecomunica, WPARAM wParam, LPARAM lParam)
{
    switch (mensajecomunica) /* Manejamos los mensajes */
    {
    case WM_CREATE:
        SetWindowPos(ventana1, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        /*LA linea anterior es para mantener la ventana encima de todas las demás del sistema
        Note: SWP_NOMOVE | SWP_NOSIZE are for ignoring 3rd, 4th, 5th, 6th parameters of the SetWindowPos function.
        The second parameter can be:
        HWND_BOTTOM
        HWND_NOTOPMOST (set window to be a normal window)
        HWND_TOP
        HWND_TOPMOST (set window to be always on top)*/
        break;
    case WM_COMMAND:
        if (LOWORD(Btn1) == wParam)
        {
            int nLength = GetWindowTextLengthW(TxtcajaTexto);
            if (nLength < 1)
                break; // si no hay texto en la caja no prosigue
            /*  if (MessageBox(0, "Seguro de Mandar el siguiente texto?", "Aclaración", MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
            {  // el mesgbox lo desactive x que generaba conficto al tener una ventana en primer plano*/
            EnableWindow(GetDlgItem(ventana1, Btn1), false); // inhabilita los controles
            EnableWindow(GetDlgItem(ventana1, ID_EDIT1), false);
            // std::wstring strText; //variable de tipo std::wstring para manejar la cadena Unicode
            wchar_t *pText = new wchar_t[nLength + 1];
            GetWindowTextW(TxtcajaTexto, pText, nLength + 1); // obtengo el texto del textbox
            EjecutarHotKey(VK_MENU, VK_TAB);                  // pretende dar foco a la ventana anterior
            Sleep(1000);                                      // aguanta un segundo por si el equipo es lento al cambiar ventana
            TipeaTexto(pText, nLength);                       // HACE LA MAGIA
            // SetWindowText(TxtcajaTexto, Sabana); //cadena normal en textbox
            //  SetWindowTextW(TxtcajaTexto, pText); // coloca cadena UNICODE en textbox
            delete[] pText;
            EnableWindow(GetDlgItem(ventana1, Btn1), true); // Habilita los controles
            EnableWindow(GetDlgItem(ventana1, ID_EDIT1), true);
            //}
        }
        else if (LOWORD(Btn2) == wParam)
        {
            SetWindowText(TxtcajaTexto, "");
            SetFocus(TxtcajaTexto);
        }
        else if (LOWORD(Btn3) == wParam)
        {
            SetFocus(TxtcajaTexto);
            SendMessage(TxtcajaTexto, EM_SETSEL, 0, -1); // selecciona todo el texto del textbox
            EjecutarHotKey(VK_CONTROL, 0x43);            // Ctrl + C; Copia
            EjecutarHotKey(VK_RIGHT, 0);                 // Tecla derecha para deseleccionar
        }
        else if (LOWORD(Btn4) == wParam)
        {
            SetFocus(TxtcajaTexto);
            EjecutarHotKey(VK_CONTROL, 0x56); // Ctrl + V; PEga texto
        }
        else if (LOWORD(ID_LINK) == wParam)
        {
            // Abrir el enlace en el navegador predeterminado al hacer click en label
            ShellExecute(NULL, "open", "https://github.com/Armando8bits", NULL, NULL, SW_SHOWNORMAL);
        }
        break;
    case WM_CLOSE:               /* Que hacer en caso de recibir el mensaje WM_CLOSE*/
        DestroyWindow(ventana1); /* Destruir la ventana */
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_NCACTIVATE: // da el foco al txtbox cada q la ventana tiene el foco, no se si sea optimo hacerlo asi
        SetFocus(TxtcajaTexto);
        break;
    default: /* Tratamiento por defecto para mensajes que no especificamos */
        return DefWindowProc(ventana1, mensajecomunica, wParam, lParam);
    }
    return 0;
}

void TipeaTexto(wchar_t *Cadena, int Largo)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = 0; // Inicializar el valor una vez fuera del bucle

    std::vector<INPUT> inputBuffer; // Búfer para acumular las teclas presionadas

    for (int indice = 0; indice < Largo; indice++)
    {
        wchar_t actual = Cadena[indice];
        int CodAscii = int(actual); // Convierte el carácter a ASCII (int)

        if (CodAscii == 13)
        {
            /*EjecutarHotKey(VK_RETURN, 0);
            continue; */
            CodAscii=32; //reemplaza el salto de linea por un Espacio
            /*La unica falla es que deja dos espacios al inicio del parrafo, hay que averiguar como 
            se llama el caracter que va junto al enter para omitirlo, creo que esa es la falla*/
        } 

        // Presionar una "tecla" Unicode
        ip.ki.dwFlags = KEYEVENTF_UNICODE;
        ip.ki.wScan = CodAscii; // Es mejor utilizar un código hexadecimal en lugar de ASCII

        // Acumular la tecla presionada en el búfer
        inputBuffer.push_back(ip);

        // Liberar la tecla en el búfer
        ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
        inputBuffer.push_back(ip);
    }

    // Enviar todas las teclas presionadas de una vez
    SendInput(inputBuffer.size(), inputBuffer.data(), sizeof(INPUT));
}

void EjecutarHotKey(int Tecla1, int Tecla2)
{
    int TECLA[2] = {Tecla1, Tecla2};

    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    for (int i = 0; i < 2; i++)
    {
        // Press the "Ctrl" key
        ip.ki.wVk = TECLA[i];
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));
    }
    for (int i = 1; i > -1; i--) // orden inverso
    {
        // Release the "Ctrl" key
        ip.ki.wVk = TECLA[i];
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
}
