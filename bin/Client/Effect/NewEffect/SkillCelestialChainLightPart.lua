-- 메시 하나 출력
Begin("Parent");
InitPos(0, 0, 0);
End();

Begin("ParticleSystem");
InitPos(0,0,0);
InitTextureName("Res\\Texture\\flare.bmp");
InitLoop(1);
InitSpawnBoundingBox(-10, 10, -10, 10, -10, 10);
InitColor(55,100,150,150);
InitParticleNum(10);
InitEmitRate(10);
InitSize(30,30);
End();

