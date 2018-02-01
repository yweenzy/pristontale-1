-- 메시 하나 출력
Begin("Parent");
InitPos(0, 20, 0);
End();

Begin("Mesh");
InitMeshName("Res\\Object\\at_4-3.ASE");
InitMaxFrame(20);
InitLoop(1);
InitColor(255,255,255,5);
EventFadeColor(0,255,255,255,0);
EventFadeColor(0.2,255,255,255,50);
EventFadeColor(0.4,255,255,255,150);
EventFadeColor(0.5,255,255,255,50);
End();

Begin("ParticleSystem");
InitPos(0,0,0);
InitSize(2,2);
InitVelocity(-20, 20, -10, 10, -15, 15);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-30, 30, 0, 20, -30, 30);
InitColor(255,255,255,250);
InitParticleNum(20);
InitEmitRate(30);
InitEndTime(0.2,0.8);
End();

Begin("ParticleSystem");
InitSize(50,50);
InitVelocity(-20,20,0,10,-20,20);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-30, 30, 0, 10, -30, 30);
InitColor(255,255,255,50);
InitParticleNum(15);
InitEmitRate(30);
InitEndTime(0.4,0.6);
End();