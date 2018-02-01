-- 메시 하나 출력
Begin("Parent");
InitPos(0, -5, 0);
End();


Begin("ParticleSystem");
InitPos(0,10,0);
InitSize(2,2);
InitVelocity(-10,10,10,30,-20,20);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-20, 20, 0, 50, -20, 0);
InitColor(255,255,255,250);
InitParticleNum(20);
InitEmitRate(30);
InitEndTime(0.2,0.5);
End();

Begin("ParticleSystem");
InitPos(0,10,-40);
InitSize(2,2);
InitVelocity(-10,10,10,30,-20,20);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-20, 20, 0, 50, -20, 0);
InitColor(255,255,255,250);
InitParticleNum(20);
InitEmitRate(30);
InitEndTime(0.2,0.5);
End();

Begin("ParticleSystem");
InitPos(0,10,-40);
InitSize(2,2);
InitVelocity(-10,10,10,30,-20,20);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-20, 20, 0, 50, -20, 0);
InitColor(255,255,255,250);
InitParticleNum(20);
InitEmitRate(30);
InitEndTime(0.2,0.5);
End();

Begin("ParticleSystem");
InitPos(0,10,0);
InitSize(40,40);
InitVelocity(-10,10,10,10,0,0);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-20, 20, 0, 10, -20, 20);
InitColor(200,200,255,40);
InitParticleNum(24);
InitEmitRate(20);
InitEndTime(0.2,0.3);
End();

Begin("ParticleSystem");
InitPos(0,10,-50);
InitSize(50,50);
InitVelocity(-10,10,10,35,0,10);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-50, 50, 0, 10, -30, 0);
InitColor(200,200,200,50);
InitParticleNum(24);
InitEmitRate(20);
InitEndTime(0.3,0.5);
End();



