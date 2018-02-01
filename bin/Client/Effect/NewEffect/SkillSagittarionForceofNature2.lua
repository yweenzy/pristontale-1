-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();

Begin("ParticleSystem");
InitTextureName("Res\\TextureHit\\wind4_101.bmp");
InitPos(0,60,0);
InitSize(0.2,2,3,40);
InitEndTime(0.8,1);
InitLoop(0);
InitSpawnBoundingSphere(1,1);
InitVelocity(2,0.1,-3,3,-3,3);
InitColor(255,255,255,0);
InitEmitRate(30);
InitParticleType("BillboardAxial");
InitVelocityType("curpos");
InitStartDelayTime(1);
EventFadeColor(0,   255,150,50,0);
EventFadeColor(0.3,255,150,50,255);
EventFadeColor(0.7,255,150,50,255);
EventFadeColor(1,   255,150,50,0);
End();

Begin("Billboard");
InitPos(0,60,0);
InitTextureName("Res\\TextureHit\\circle_009.bmp");
InitColor(255,255,255,255);
InitSize(30,30);
InitEndTime(1);
InitLoop(0);
InitStartDelayTime(1);
EventFadeColor(0,   255,255,50,150);
EventFadeColor(0.4,255,255,50,255);
EventFadeColor(0.6,255,255,50,255);
EventFadeColor(1,   255,255,50,150);
End();
