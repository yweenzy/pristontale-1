-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();

Begin("ParticleSystem");
InitPos(0,0,0);
InitTextureName("Res\\TextureHit\\hit6_601.bmp");
InitLoop(2);
InitSize(20,20);
InitSpawnBoundingBox(-5, 5, -5, 5, -5, 5);
InitColor(00,160,160,150);
InitParticleNum(20);
InitEmitRate(20);
EventFadeColor(0,   0,255,255,150);
EventFadeColor(0.4,0,255,255,255);
EventFadeColor(0.6,0,255,255,255);
EventFadeColor(1,   0,255,255,0);
End();
