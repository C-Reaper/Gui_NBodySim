#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"
#include "/home/codeleaded/System/Static/Library/LSystem.h"


#define NBODYS  100000U
TransformedView tv;

void Setup(AlxWindow* w){
	tv = TransformedView_Make(
		(Vec2){ GetWidth(),GetHeight() },
		(Vec2){ 0.0f,0.0f },
		(Vec2){ 0.1f,0.1f },
		(float)GetWidth() / (float)GetHeight()
	);
    AlxFont_Resize(&window.font,50,50);

    
}

void Update(AlxWindow* w){
    tv.ZoomSpeed = (float)w->ElapsedTime;
	TransformedView_HandlePanZoom(&tv,window.Strokes,(Vec2){ GetMouse().x,GetMouse().y });
	TransformedView_Output(&tv,(Vec2){ GetWidth(),GetHeight() });
    
    

	Clear(BLACK);

    
    
    CStr_RenderAlxFontf(WINDOW_STD_ARGS,GetAlxFont(),0.0f,0.0f,RED,"B: %u",NBODYS);
}

void Delete(AlxWindow* w){
    
}

int main(){
    if(Create("N-Body-Simulation",1800,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}