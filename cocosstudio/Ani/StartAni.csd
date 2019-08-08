<GameFile>
  <PropertyGroup Name="StarAni" Type="Node" ID="49a0bb11-1f26-4bb3-b914-47ac827b8b55" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="3" Speed="1.0000">
        <Timeline ActionTag="-1182401786" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="PlistSubImage" Path="3.png" Plist="Img/game_element.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="1" Tween="False">
            <TextureFile Type="PlistSubImage" Path="2.png" Plist="Img/game_element.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="2" Tween="False">
            <TextureFile Type="PlistSubImage" Path="1.png" Plist="Img/game_element.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="3" Tween="False">
            <TextureFile Type="PlistSubImage" Path="GO.png" Plist="Img/game_element.plist" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="-1182401786" Property="BlendFunc">
          <BlendFuncFrame FrameIndex="0" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="1" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="2" Tween="False" Src="1" Dst="771" />
          <BlendFuncFrame FrameIndex="3" Tween="False" Src="1" Dst="771" />
        </Timeline>
        <Timeline ActionTag="-1182401786" Property="Alpha">
          <IntFrame FrameIndex="0" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="1" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="2" Value="255">
            <EasingData Type="0" />
          </IntFrame>
          <IntFrame FrameIndex="3" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <ObjectData Name="Node" Tag="8" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="time" ActionTag="-1182401786" Tag="11" IconVisible="False" LeftMargin="-55.5000" RightMargin="-55.5000" TopMargin="-84.5000" BottomMargin="-84.5000" ctype="SpriteObjectData">
            <Size X="111.0000" Y="169.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="2.5000" ScaleY="2.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="3.png" Plist="Img/game_element.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>