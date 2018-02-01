-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();

Begin("BillboardAxial");
InitTextureName("Res\\TextureHit\\aurora4_201.bmp");
InitColor(255,255,255,0);
InitSize(120,20);
InitPos(0,90,0);
InitEndTime(1);
InitAxialPos(0,0,0,0,200,0);
EventFadeColor(0,   255,255,255,120);
EventFadeColor(0.4,255,255,255,200);
EventFadeColor(0.6,255,255,255,200);
EventFadeColor(1,   255,255,255,120);
End();


Begin("ParticleSystem");
InitTextureName("Res\\TextureHit\\star02M_04.bmp");
InitPos(0,150,0);
InitSize(3,3);
InitEndTime(5,10);
InitVelocity(-5,5,-20,-30,-5,5);
InitLoop(0);
InitSpawnBoundingBox(-60, 60, -60, 60, -60, 60);
InitColor(255,255,255,255);
InitParticleNum(30);
InitEmitRate(30);
End();
