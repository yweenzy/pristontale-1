-- 메시 하나 출력
Begin("Parent");
InitPos(0, 20, -10);
End();

Begin("ParticleSystem");
InitTextureName("Res\\Texture\\Line_001.bmp");
InitPos(0,0,0);
InitSize(0.2,1,10,80);
InitEndTime(0.2,0.5);
InitLoop(1);
InitSpawnBoundingSphere(3,3);
InitParticleNum(25);
InitVelocity(50,80,-3,3,-3,3);
InitColor(255,255,255,255);
InitEmitRate(200);
InitParticleType("BillboardAxial");
InitVelocityType("CurPos");
EventFadeColor(0.2,255,255,255,200);
EventFadeColor(0.5,255,150,50,0);
End();

Begin("Billboard");
InitTextureName("Res\\TextureHit\\hit4_101.bmp");
InitPos(0,0,0);
InitColor(255,255,255,255);
InitSize(180,80);
InitEndTime(0.5);
InitLoop(1);
EventFadeColor(0,   255,255,255,100);
EventFadeColor(0.2,255,255,255,255);
EventFadeColor(0.5,255,255,255,200);
End();
