-- 파티클 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();

Begin("ParticleSystem");
InitTextureName("Res\\Texture\\flare.bmp");
InitPos(0,0,0);
InitSize(0.1,1,30,60);
InitEndTime(0.2,0.5);
InitLoop(1);
InitSpawnBoundingSphere(1,1);
InitVelocity(20,80,-3,3,-3,3);
InitColor(255,150,50,255);
InitEmitRate(120);
InitParticleNum(25);
InitParticleType("BillboardAxial");
InitVelocityType("CurPos");
EventFadeColor(0,   255,150,50,255);
EventFadeColor(0.1,255,150,50,255);
EventFadeColor(0.3,255,150,50,0);
End();

Begin("ParticleSystem");
InitTextureName("Res\\Texture\\flare2.bmp");
InitPos(0,0,0);
InitSize(0.6,0.7,20,40);
InitEndTime(0.2,0.6);
InitLoop(1);
InitSpawnBoundingSphere(1,1);
InitVelocity(40,90,-3,3,-3,3);
InitColor(255,255,255,255);
InitEmitRate(200);
InitParticleNum(20);
InitParticleType("BillboardAxial");
InitVelocityType("CurPos");
EventFadeColor(0,   255,255,255,255);
EventFadeColor(0.1,255,255,255,255);
EventFadeColor(0.5,255,255,255,0);
End();

Begin("Billboard");
InitTextureName("Res\\Texture\\flare2.bmp");
InitPos(0,0,0);
InitColor(255,255,255,0);
InitSize(100,100);
InitEndTime(0.3);
InitLoop(1);
EventFadeColor(0,   255,150,50,80);
EventFadeColor(0.1,255,255,255,220);
EventFadeColor(0.3,255,150,50,0);
End();

