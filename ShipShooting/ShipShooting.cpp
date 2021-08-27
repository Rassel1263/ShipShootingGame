//-----------------------------------------------------------------------------
// File: ShipShooting.cpp
//
// Desc: Better than just lights and materials, 3D objects look much more
//       convincing when texture-mapped. ShipShooting can be thought of as a sort
//       of wallpaper, that is shrinkwrapped to fit a texture. ShipShooting are
//       typically loaded from image files, and D3DX provides a utility to
//       function to do this for us. Like a vertex buffer, ShipShooting have
//       Lock() and Unlock() functions to access (read or write) the image
//       data. ShipShooting have a width, height, miplevel, and pixel format. The
//       miplevel is for "mipmapped" ShipShooting, an advanced performance-
//       enhancing feature which uses lower resolutions of the texture for
//       objects in the distance where detail is less noticeable. The pixel
//       format determines how the colors are stored in a texel. The most
//       common formats are the 16-bit R5G6B5 format (5 bits of red, 6-bits of
//       green and 5 bits of blue) and the 32-bit A8R8G8B8 format (8 bits each
//       of alpha, red, green, and blue).
//
//       ShipShooting are associated with geometry through texture coordinates.
//       Each vertex has one or more sets of texture coordinates, which are
//       named tu and tv and range from 0.0 to 1.0. Texture coordinates can be
//       supplied by the geometry, or can be automatically generated using
//       Direct3D texture coordinate generation (which is an advanced feature).
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include "Header.h"
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )



//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------



// Our custom FVF, which describes our custom vertex structure
#ifdef SHOW_HOW_TO_USE_TCI
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#else
#endif



//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{

}







//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    UNREFERENCED_PARAMETER( hInst );

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        L"D3D Tutorial", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 05: ShipShooting",
                              WS_POPUP, 0, 0, Game::GetInstance().screenWidth, Game::GetInstance().screenHeight,
                              NULL, NULL, wc.hInstance, NULL );

    Game::GetInstance().Check();
    // Initialize Direct3D
    if( SUCCEEDED( Game::GetInstance().Init( hWnd ) ) )
    {
            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof( msg ) );
            while( msg.message != WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
                {
                    Game::GetInstance().Update(1 / 60.0f);
                    Game::GetInstance().Render();
                }
            }
    }

    UnregisterClass( L"D3D Tutorial", wc.hInstance );
    return 0;
}



