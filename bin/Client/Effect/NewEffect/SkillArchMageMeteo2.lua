-- 메시 하나 출력
Begin("Parent");
InitPos(0, 20, 0);
End();

-- 운석덩어리

Begin("ParticleSystem");
InitPos(0,60,0);
InitVelocity(-10,10,10,70-10,-10);
InitTextureName("Res\\TextureHit\\Fire4_102.bmp");
InitLoop(0);
InitSpawnBoundingBox(-10, 10, -10, 10, -10, 10);
InitColor(255,255,255,60);
InitParticleNum(50);
InitEmitRate(40);
End();

Begin("ParticleSystem");
InitPos(0,57,0);
InitVelocity(-5,5,-5,20,-5,-5);
InitTextureName("Res\\TextureHit\\fire_001.bmp");
InitLoop(0);
InitSpawnBoundingBox(-5, 5, -5,5, -5, 5);
InitColor(255,255,255,30);
InitParticleNum(30);
InitEmitRate(20);
End();

Begin("Mesh");
InitMeshName("Res\\Object\\MG_4-4.ASE");
InitPos(0,55,0);
InitMaxFrame(20);
InitLoop(0);
InitColor(255,255,255,240);
End();

-- 타격 이팩트

Begin("Billboard");
InitAniTextureName("Res\\TextureHit\\hit5_50.bmp", 6, 0.1);
InitPos(0,10,0);
InitColor(255,255,255,0);
InitSize(100,100);
InitEndTime(0.6);
InitLoop(0);
EventFadeColor(0,   250,150,50,100);
EventFadeColor(0.2,250,180,50,255);
EventFadeColor(0.4,250,150,50,255);
EventFadeColor(0.6,250,120,50,255);
EventFadeColor(0.8,250,150,50,100);
End();


Begin("Mesh");
InitMeshName("Res\\Object\\MG_4-42-16.ASE");
InitMaxFrame(16);
InitLoop(0);
InitColor(255,255,255,255);
EventFadeColor(0,255,255,255,250);
EventFadeColor(0.2,255,255,255,255);
EventFadeColor(0.6,255,255,255,0);
End();

-- 메쉬 두번 찍음
Begin("Mesh");
InitMeshName("Res\\Object\\MG_4-42-16.ASE");
InitMaxFrame(16);
InitLoop(0);
InitColor(255,255,255,255);
EventFadeColor(0,255,255,255,250);
EventFadeColor(0.2,255,255,255,255);
EventFadeColor(0.4,255,255,255,0);
End();



