-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();

Begin("Billboard");
InitAniTextureName("Res\\TextureHit\\light4_10.bmp", 3, 0.02);
InitPos(0,80,0);
InitColor(255,255,255,255);
InitSize(60,60);
InitEndTime(1);
InitLoop(1);
EventFadeColor(0,   255,255,255,150);
EventFadeColor(0.4,255,255,255,255);
EventFadeColor(0.6,255,255,255,255);
EventFadeColor(1,   255,255,255,150);
End();
