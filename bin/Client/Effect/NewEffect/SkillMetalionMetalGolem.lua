-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();

Begin("Mesh");
InitMeshName("Res\\Object\\MC_4-4.ASE");
InitMaxFrame(60);
InitPos(0,0,0);
InitLoop(1);
InitColor(255,255,255,255);
EventFadeColor(0,255,255,255,255);
EventFadeColor(1.4,255,255,255,255);
EventFadeColor(1.8,255,255,255,50);
End();

Begin("ParticleSystem");
InitTextureName("Res\\TextureHit\\wind4_101.bmp");
InitPos(0,0,0);
InitSize(0.2,1.2,30,60);
InitEndTime(0.8,1);
InitLoop(1);
InitSpawnBoundingSphere(1,1);
InitVelocity(2,0.1,-3,3,-3,3);
InitColor(255,255,255,0);
InitEmitRate(30);
InitParticleType("BillboardAxial");
InitVelocityType("curpos");
EventFadeColor(0,   150,250,255,0);
EventFadeColor(0.3,150,250,255,230);
EventFadeColor(0.7,150,250,255,255);
EventFadeColor(1,   150,250,255,0);
End();

Begin("Billboard");
InitPos(0,0,0);
InitTextureName("Res\\TextureHit\\circle_009.bmp");
InitColor(255,255,255,255);
InitSize(30,30);
InitEndTime(1);
InitLoop(2);
EventFadeColor(0,   0,255,200,150);
EventFadeColor(0.4,0,255,200,255);
EventFadeColor(0.6,0,255,200,255);
EventFadeColor(1,   0,255,200,150);
End();



