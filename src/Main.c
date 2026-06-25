#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/NBodySim.h"


NBodySim nbs;

void Setup(AlxWindow* w){
	nbs = NBodySim_New(1000U,1000U);
    AlxFont_Resize(&window.font,50,50);
}

void Update(AlxWindow* w){
    NBodySim_Input(&nbs,w->Strokes,GetMouse());

	if(Stroke(ALX_MOUSE_L).DOWN){
		const Vec2 velo = TransformedView_ScreenWorldLength(&nbs.tv,Vec2_Sub(GetMouse(),GetMouseBefore()));
		const Vec2 pm = TransformedView_ScreenWorldPos(&nbs.tv,GetMouse());
		const float r = (float)Random_f64_MinMax(0.5f,1.0f);
		
		NBody nb = NBody_New(
			WHITE,
			pm.x,
			pm.y,
			r * 10.0f,
			r
		);
		nb.vx = velo.x * 3.0f;
		nb.vy = velo.y * 3.0f;

		NBodySim_Add(&nbs,&nb);
	}
	if(Stroke(ALX_MOUSE_R).PRESSED){
		const Vec2 pm = TransformedView_ScreenWorldPos(&nbs.tv,GetMouse());
		const float r = 30.0f;//(float)Random_f64_MinMax(10.0f,11.0f);

		NBodySim_Add(&nbs,(NBody[]){
			NBody_New(
				WHITE,
				pm.x,
				pm.y,
				r * 1000.0f,
				r
			)
		});
	}

    NBodySim_Update(&nbs,w->ElapsedTime);

	Clear(BLACK);

    NBodySim_Render(&nbs,WINDOW_STD_ARGS);
}

void Delete(AlxWindow* w){
    NBodySim_Free(&nbs);
}

int main(){
    if(Create("N-Body-Simulation",1900,1100,1,1,Setup,Update,Delete))
        Start();
    return 0;
}