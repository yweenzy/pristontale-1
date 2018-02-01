-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();

Begin("BillboardAxial");
InitAniTextureName("Res\\TextureHit\\R_e00.bmp", 3, 0.02);
InitPos(0,40,0);
InitAxialPos(0,0,0,0,0,-100);
InitColor(0,255,255,255);
InitSize(20,10);
InitEndTime(1);
EventFadeColor(0,   0,255,255,150);
EventFadeColor(0.4,0,255,255,255);
EventFadeColor(0.6,0,255,255,255);
EventFadeColor(1,   0,255,255,150);
End();

