-- 메시 하나 출력
Begin("Parent");
InitPos(0, 10, 0);
End();

Begin("CreateMesh");
InitColor(255,255,255,0)
InitPos(0,0,0);
InitEndTime(0.7);
InitLoop(1);
InitTextureName("Res\\Texture\\circle.bmp");
InitSize(40,40);
InitColor(255,255,255,100);
EventFadeColor(0,0,0,0)
EventFadeColor(0.2,255,255,255,100);
EventFadeColor(0.5,255,255,255,0);
EventSize(0,40,40,0);
EventFadeSize(0.7,400,500,0);
End();

Begin("CreateMesh");
InitColor(255,255,255,0)
InitPos(0,0,0);
InitEndTime(0.7);
InitLoop(1);
InitTextureName("Res\\TextureHit\\blow_003.bmp");
InitSize(40,40);
InitColor(255,150,50,150);
EventFadeColor(0,0,0,0)
EventFadeColor(0.2,255,150,50,150);
EventFadeColor(0.5,255,150,50,0);
EventSize(0,40,40,0);
EventFadeSize(0.7,700,800,0);
End();


