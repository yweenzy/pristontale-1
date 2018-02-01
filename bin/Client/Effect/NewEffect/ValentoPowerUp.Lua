-- 파티클 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();

Begin("ParticleSystem");
InitTextureName("Res\\Texture\\flare.bmp");
InitPos(-19,56,0);
InitSize(0.5,2,60,70);
InitEndTime(0.5,0.5);
InitLoop(1);
InitSpawnBoundingSphere(70,100);
InitVelocity(-110,-60,-3,3,-3,3);
InitColor(255,255,255,50);
InitEmitRate(1000);
InitParticleType("BillboardAxial");
InitVelocityType("CurPos");
EventFadeColor(0, 255,150,50,255);
EventFadeColor(0.2, 255,80,30,255);
EventFadeColor(0.5, 255,30,10,0);
End();

