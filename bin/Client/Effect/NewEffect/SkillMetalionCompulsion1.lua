-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();

Begin("ParticleSystem");
InitTextureName("Res\\Texture\\flare.bmp");
InitPos(0,20,0);
InitSize(0.5,1,60,150);
InitEndTime(0.5,0.5);
InitLoop(2);
InitSpawnBoundingSphere(150,150);
InitVelocity(-110,-60,-3,3,-3,3);
InitColor(255,255,255,50);
InitEmitRate(100);
InitParticleType("BillboardAxial");
InitVelocityType("CurPos");
EventFadeColor(0, 255,150,50,255);
EventFadeColor(0.2, 255,150,50,255);
EventFadeColor(0.5, 255,150,50,0);
End();

Begin("BillboardAxial");
InitTextureName("Res\\Texture\\flare.bmp");
InitColor(255,255,255,0);
InitLoop(1);
InitSize(20,20);
InitEndTime(1);
InitStartDelayTime(0.2);
InitAxialPos(0,0,0,0,80,0);
EventFadeColor(0,   255,150,50,100);
EventFadeColor(0.4,255,150,50,255);
EventFadeColor(0.8,255,150,50,255);
EventFadeColor(1,   255,150,50,0);
End();

-- 밖으로 나오는
Begin("Mesh");
InitMeshName("Res\\Object\\Roar.ASE");
-- 최대 프레임 40이다.
InitMaxFrame(15);
InitLoop(1);
InitStartDelayTime(1);
EventFadeColor(0,0,0,0,0);
EventFadeColor(0.2,80,180,255,255);
EventFadeColor(0.4,0,0,0,0);
End();

Begin("Mesh");
InitMeshName("Res\\Object\\Roar.ASE");
-- 최대 프레임 40이다.
InitMaxFrame(15);
InitLoop(1);
InitStartDelayTime(1.05);
EventFadeColor(0,0,0,0,0);
EventFadeColor(0.2,50,100,255,255);
EventFadeColor(0.4,0,0,0,0);
End();

Begin("Mesh");
InitMeshName("Res\\Object\\Roar.ASE");
-- 최대 프레임 40이다.
InitMaxFrame(15);
InitPos(0,0,0)
InitLoop(1);
InitStartDelayTime(1.1);
EventFadeColor(0,0,0,0,0);
EventFadeColor(0.2,80,180,255,255);
EventFadeColor(0.4,0,0,0,0);
End();

Begin("CreateMesh");
InitColor(255,255,255,0)
InitPos(0,10,0);
InitEndTime(0.4);
InitLoop(1);
InitStartDelayTime(1);
InitTextureName("Res\\Texture\\circle.bmp");
InitSize(40,40);
EventFadeColor(0,0,0,0,0);
EventFadeColor(0.2,255,255,255,100);
EventFadeColor(0.4,255,255,255,0);
EventFadeSize(0,0,0,0);
EventFadeSize(0.4,300,300,0);
End();

Begin("CreateMesh");
InitTextureName("Res\\Texture\\circle.bmp");
InitColor(255,255,255,0)
InitPos(0,10,0);
InitStartDelayTime(1.1);
InitEndTime(0.3);
InitLoop(1);
InitSize(40,40);
EventFadeColor(0,0,0,0,0);
EventFadeColor(0.1,100,100,255,100);
EventFadeColor(0.3,100,100,255,0);
EventFadeSize(0,0,0,0);
EventFadeSize(0.3,300,300,0);
End();




