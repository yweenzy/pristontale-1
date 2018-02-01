-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, 3);
End();

Begin("Mesh");
InitMeshName("Res\\Object\\Roar.ASE");
-- 최대 프레임 40이다.
InitMaxFrame(15);
InitLoop(1);
EventFadeColor(0,0,0,0,0);
EventFadeColor(0.2,180,230,255,120);
EventFadeColor(0.4,0,0,0,0);
End();

Begin("Mesh");
InitMeshName("Res\\Object\\Roar.ASE");
-- 최대 프레임 40이다.
InitMaxFrame(15);
InitLoop(1);
InitStartDelayTime(0.05);
EventFadeColor(0,0,0,0,0);
EventFadeColor(0.2,200,230,255,150);
EventFadeColor(0.4,0,0,0,0);
End();

Begin("CreateMesh");
InitColor(200,255,255,0)
InitPos(0,10,0);
InitEndTime(0.4);
InitLoop(1);
InitTextureName("Res\\Texture\\circle.bmp");
InitSize(40,40);
EventFadeColor(0,0,0,0,0);
EventFadeColor(0.2,200,255,255,120);
EventFadeColor(0.4,200,255,255,0);
EventFadeSize(0,0,0,0);
EventFadeSize(0.4,250,250,0);
End();

Begin("CreateMesh");
InitColor(255,255,255,0)
InitPos(0,10,0);
InitEndTime(0.3);
InitLoop(1);
InitTextureName("Res\\Texture\\circle.bmp");
InitSize(40,40);
InitStartDelayTime(0.1);
EventFadeColor(0,0,0,0,0);
EventFadeColor(0.1,255,200,255,120);
EventFadeColor(0.3,255,200,255,0);
EventFadeSize(0,0,0,0);
EventFadeSize(0.3,250,250,0);
End();

