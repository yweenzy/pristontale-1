-- 메시 하나 출력
Begin("Parent");
InitPos(0, 30, 0);
End();

Begin("ParticleSystem");
InitPos(0,0,0);
InitSize(40,40);
InitVelocity(-5,5,-0,5,5,5);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-5, 5, -0, 5, -5, 5);
InitColor(255,255,255,70);
EventFadeColor(0,   255,255,255,0);
EventFadeColor(0.2,255,255,255,60);
EventFadeColor(0.5,   255,255,255,0);
InitParticleNum(6);
InitEmitRate(6);
InitEndTime(1);
End();

-- 떨어지기
Begin("Mesh");
InitPos(0, -25, 0);
InitMeshName("Res\\Object\\At_4-3a.ASE");
InitMaxFrame(20);
InitLoop(1);
InitColor(255,255,255,150);
InitBlendType("color");
End();

Begin("Mesh");
InitPos(0, -25, 0);
InitMeshName("Res\\Object\\At_4-3a.ASE");
InitMaxFrame(20);
InitLoop(1);
InitColor(255,255,255,30);
InitBlendType("lamp");

End();


Begin("ParticleSystem");
InitPos(0,-25,0);
InitSize(40,40);
InitVelocity(-15,15,-10,15,15,15);
InitTextureName("Res\\TextureHit\\ice_001.bmp");
InitLoop(1);
InitSpawnBoundingBox(-25, 25, -10, 15, -15, 15);
InitColor(255,255,255,70);
EventFadeColor(0,   255,255,255,0);
EventFadeColor(0.2,255,255,255,60);
EventFadeColor(0.5,   255,255,255,0);
InitParticleNum(12);
InitEmitRate(10);
InitEndTime(1);
End();