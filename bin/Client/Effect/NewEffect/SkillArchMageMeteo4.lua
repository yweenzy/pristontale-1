-- 메시 하나 출력
Begin("Parent");
InitPos(0,10,0);
End();

Begin("ParticleSystem");
InitPos(0,20,-5);
InitSize(40,40);
InitVelocity(-10,10,-10,45,-10,10);
InitTextureName("Res\\TextureHit\\Fire5_101.bmp");
InitLoop(1);
InitSpawnBoundingBox(-7, 7, -10, 10, 8, 8);
InitColor(55,255,55,150);
InitParticleNum(20);
InitEmitRate(20);
End();

Begin("ParticleSystem");
InitPos(0,10,-5);
InitSize(30,30);
InitVelocity(-10,10,-10,35,-10,10);
InitTextureName("Res\\TextureHit\\Fire5_101.bmp");
InitLoop(1);
InitSpawnBoundingBox(-7, 7, -10, 20, 8, 8);
InitColor(255,0,0,250);
InitParticleNum(15);
InitEmitRate(15);
End();

Begin("ParticleSystem");
InitPos(0,10,-3);
InitSize(20,20);
InitVelocity(-10,10,-10,20,-10,10);
InitTextureName("Res\\TextureHit\\Fire5_101.bmp");
InitLoop(1);
InitSpawnBoundingBox(-7, 7, -10, 0, 8, 8);
InitColor(255,150,0,200);
InitParticleNum(10);
InitEmitRate(10);
End();

Begin("Mesh");
InitMeshName("Res\\Object\\MG_4-42.ASE");
InitBlendType("shadow");
InitMaxFrame(16);
InitLoop(1);
InitColor(255,255,255,255);
EventFadeColor(255,255,255,255,255);
End();

Begin("CreateMesh");
InitColor(255,255,255,0)
InitPos(0,0,0);
InitEndTime(0.4);
InitLoop(1);
InitTextureName("Res\\Texture\\circle.bmp");
InitSize(40,40);
InitColor(255,255,255,150);
EventFadeColor(0,0,0,0)
EventFadeColor(0.2,255,200,200,30);
EventFadeColor(0.3,255,200,200,0);
EventSize(0,40,40,0);
EventFadeSize(0.5,500,500,0);
End();