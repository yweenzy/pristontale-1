-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, -30);
End();

Begin("ParticleSystem");
InitPos(0,5,0);
InitSize(40,40);
InitVelocity(-10,10,10,10,0,0);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-20, 20, 0, 10, -20, 20);
InitColor(255,255,255,40);
InitParticleNum(12);
InitEmitRate(20);
InitEndTime(0.5,0.7);
End();

Begin("ParticleSystem");
InitPos(0,5,-30);
InitSize(50,50);
InitVelocity(-10,10,10,30,0,0);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-30, 30, 0, 10, 0, 0);
InitColor(255,255,255,30);
InitParticleNum(12);
InitEmitRate(20);
InitEndTime(0.6,0.8);
End();

Begin("ParticleSystem");
InitPos(0,5,-50);
InitSize(60,60);
InitVelocity(-10,10,10,30,0,-20);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-40, 40, 0, 10, -60, 0);
InitColor(255,255,255,50);
InitParticleNum(12);
InitEmitRate(20);
InitEndTime(0.7,0.9);
End();

Begin("Mesh");
InitMeshName("Res\\Object\\Nt_4-4.ASE");
InitMaxFrame(16);
InitPos(0, 0, 0);
InitLoop(1);
InitColor(255,255,255,0);
EventFadeColor(0,255,255,255,50);
EventFadeColor(0.2,255,255,255,100);
EventFadeColor(0.4,255,255,255,100);
EventFadeColor(0.6,255,255,255,0);
End();


Begin("Mesh");
InitMeshName("Res\\Object\\Nt_4-41.ASE");
InitMaxFrame(18);
InitPos(0, 0, 0);
InitLoop(1);
InitColor(255,255,255,0);
EventFadeColor(0,255,255,255,0);
EventFadeColor(0.3,255,255,255,50);
EventFadeColor(0.5,255,255,255,100);
EventFadeColor(0.7,255,255,255,0);
End();

Begin("Mesh");
InitMeshName("Res\\Object\\Nt_4-42.ASE");
InitMaxFrame(20);
InitPos(0, 0, 0);
InitLoop(1);
InitColor(255,255,255,0);
EventFadeColor(0,255,255,255,0);
EventFadeColor(0.4,255,255,255,0);
EventFadeColor(0.6,255,255,255,100);
EventFadeColor(0.8,255,255,255,0);
End();

