<GameFile>
  <PropertyGroup Name="TeachAni" Type="Node" ID="68f5b3db-e974-4900-bdb4-6bf481af2287" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="7" Speed="1.0000">
        <Timeline ActionTag="373600833" Property="Scale">
          <ScaleFrame FrameIndex="3" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="4" X="-1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="373600833" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="PlistSubImage" Path="prompt_touch1.png" Plist="Img/game_element.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="1" Tween="False">
            <TextureFile Type="PlistSubImage" Path="prompt_touch2.png" Plist="Img/game_element.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="2" Tween="False">
            <TextureFile Type="PlistSubImage" Path="prompt_touch3.png" Plist="Img/game_element.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="3" Tween="False">
            <TextureFile Type="PlistSubImage" Path="prompt_touch4.png" Plist="Img/game_element.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="4" Tween="False">
            <TextureFile Type="PlistSubImage" Path="prompt_touch1.png" Plist="Img/game_element.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="5" Tween="False">
            <TextureFile Type="PlistSubImage" Path="prompt_touch2.png" Plist="Img/game_element.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="6" Tween="False">
            <TextureFile Type="PlistSubImage" Path="prompt_touch3.png" Plist="Img/game_element.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="7" Tween="False">
            <TextureFile Type="PlistSubImage" Path="prompt_touch4.png" Plist="Img/game_element.plist" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="373600833" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="0" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="1" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="2" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="3" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="4" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="5" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="6" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="7" Tween="False" Src="1" Dst="771" />
        </Timeline>
      </Animation>
      <ObjectData Name="Node" Tag="15" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="prompt_bg" ActionTag="-37158582" Tag="25" IconVisible="False" LeftMargin="-683.0000" RightMargin="-683.0000" TopMargin="-768.0000" BottomMargin="-768.0000" ctype="SpriteObjectData">
            <Size X="1366.0000" Y="1536.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Img/prompt_bg.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="prompt" ActionTag="373600833" Tag="26" IconVisible="False" LeftMargin="-232.0000" RightMargin="-232.0000" TopMargin="-247.5000" BottomMargin="-247.5000" ctype="SpriteObjectData">
            <Size X="464.0000" Y="495.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="-1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="prompt_touch4.png" Plist="Img/game_element.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>