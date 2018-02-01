-- 메시 하나 출력
Begin("Parent");
InitPos(0, -5, -20);
End();

Begin("Mesh");
InitMeshName("Res\\Object\\PT_4-1-25.ASE");
InitMaxFrame(25);
InitLoop(1);
InitColor(255,255,255,0);
EventFadeColor(0,255,255,255,50);
EventFadeColor(0.2,255,255,255,70);
EventFadeColor(0.5,255,255,255,50);
End();

Begin("ParticleSystem");
InitPos(0,10,0);
InitSize(2,2);
InitVelocity(-10,10,10,30,-20,20);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-20, 20, 0, 50, -20, 0);
InitColor(255,255,255,250);
InitParticleNum(10);
InitEmitRate(30);
InitEndTime(0.2,1);
End();

Begin("ParticleSystem");
InitPos(0,10,-40);
InitSize(2,2);
InitVelocity(-10,10,10,30,-20,20);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-20, 20, 0, 50, -20, 0);
InitColor(255,255,255,250);
InitParticleNum(10);
InitEmitRate(30);
InitEndTime(0.2,1);
End();

Begin("ParticleSystem");
InitPos(0,10,0);
InitSize(40,40);
InitVelocity(-10,10,10,10,0,0);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-20, 20, 0, 10, -20, 20);
InitColor(200,200,255,40);
InitParticleNum(12);
InitEmitRate(20);
InitEndTime(0.2,0.7);
End();

Begin("ParticleSystem");
InitPos(0,10,-50);
InitSize(50,50);
InitVelocity(-10,10,10,30,0,0);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-50, 50, 0, 10, -30, 0);
InitColor(200,200,200,30);
InitParticleNum(12);
InitEmitRate(20);
InitEndTime(0.4,1.2);
End();

Begin("ParticleSystem");
InitPos(0,10,-100);
InitSize(60,60);
InitVelocity(-10,10,10,30,0,0);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-60, 60, 0, 10, -40, 0);
InitColor(200,200,200,50);
InitParticleNum(12);
InitEmitRate(20);
InitEndTime(0.5,1.5);
End();


