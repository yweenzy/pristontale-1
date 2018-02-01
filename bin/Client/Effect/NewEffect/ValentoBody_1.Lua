-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();



Begin("ParticleSystem");
InitTextureName("Res\\TextureHit\\star02Y_04.bmp");
InitPos(0,2,0);
InitVelocity(-5,5,30,60,-5,5);
InitLoop(0);
InitSize(5,5);
InitSpawnBoundingDoughnut(15,15,10,10);
InitColor(123,50,132,255);
InitParticleNum(30);
InitEmitRate(30);
InitEndTime(1,2);
End();

Begin("CreateMesh");
InitTextureName("Res\\Texture\\flare.bmp");
InitPos(0,10,0);
InitColor(123,45,132,255);
InitSize(180,180);
InitLoop(0);
InitEndTime(1);
EventFadeColor(0,   123,45,132,150);
EventFadeColor(0.4,123,45,132,255);
EventFadeColor(0.6,123,45,132,255);
EventFadeColor(1,   123,45,132,150);
End();

Begin("ParticleSystem");
InitTextureName("Res\\TextureHit\\wind4_101.bmp");
InitPos(0,58,0);
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
InitPos(0,58,0);
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

Begin("ParticleSystem");
InitPos(0,50,-5);
InitSize(40,40);
InitVelocity(-10,10,-10,45,-10,10);
InitTextureName("Res\\TextureHit\\Fire5_101.bmp");
InitLoop(0);
InitSpawnBoundingBox(-7, 7, -10, 10, 8, 8);
InitColor(55,255,55,150);
InitParticleNum(20);
InitEmitRate(20);
End();

Begin("ParticleSystem");
InitPos(0,50,-5);
InitSize(30,30);
InitVelocity(-10,10,-10,35,-10,10);
InitTextureName("Res\\TextureHit\\Fire5_101.bmp");
InitLoop(0);
InitSpawnBoundingBox(-7, 7, -10, 20, 8, 8);
InitColor(255,0,0,250);
InitParticleNum(15);
InitEmitRate(15);
End();
