-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();

Begin("BillboardAxial");
InitAniTextureName("Res\\TextureHit\\R_e20.bmp", 4, 0.05);
InitPos(0,40,0);
InitAxialPos(0,0,0,0,150,0);
InitColor(255,255,255,255);
InitSize(15,10);
InitEndTime(1);
EventFadeColor(0,   255,255,255,150);
EventFadeColor(0.4,255,255,255,255);
EventFadeColor(0.6,255,255,255,255);
EventFadeColor(1,   255,255,255,150);
End();

