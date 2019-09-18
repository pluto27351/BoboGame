<GameFile>
  <PropertyGroup Name="PlayScene" Type="Scene" ID="5ad06eec-bde0-425a-aade-cbb21af8b8c3" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="30" Speed="1.0000">
        <Timeline ActionTag="1086914487" Property="Alpha">
          <IntFrame FrameIndex="0" Value="0">
            <EasingData Type="2" />
          </IntFrame>
          <IntFrame FrameIndex="15" Value="255">
            <EasingData Type="7" />
          </IntFrame>
          <IntFrame FrameIndex="30" Value="0">
            <EasingData Type="1" />
          </IntFrame>
        </Timeline>
      </Animation>
      <ObjectData Name="Scene" Tag="62" ctype="GameNodeObjectData">
        <Size X="2048.0000" Y="1536.0000" />
        <Children>
          <AbstractNodeData Name="bg" CanEdit="False" ActionTag="-849142966" Tag="20" IconVisible="False" LeftMargin="-341.5000" RightMargin="-341.5000" TopMargin="-117.5000" BottomMargin="-117.5000" ctype="SpriteObjectData">
            <Size X="2731.0000" Y="1771.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1024.0000" Y="768.0000" />
            <Scale ScaleX="0.8705" ScaleY="0.8688" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.3335" Y="1.1530" />
            <FileData Type="Normal" Path="Img/bg.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="mg_0" CanEdit="False" ActionTag="-1263650473" Tag="5" IconVisible="False" LeftMargin="-453.0000" RightMargin="-453.0000" TopMargin="-117.5000" BottomMargin="-117.5000" ctype="SpriteObjectData">
            <Size X="2954.0000" Y="1771.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1024.0000" Y="768.0000" />
            <Scale ScaleX="0.8800" ScaleY="0.8800" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.4424" Y="1.1530" />
            <FileData Type="Normal" Path="Img/mg_1.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="mg_1" CanEdit="False" ActionTag="2123528562" Alpha="238" Tag="6" IconVisible="False" LeftMargin="2146.5200" RightMargin="-3052.5200" TopMargin="-117.5000" BottomMargin="-117.5000" ctype="SpriteObjectData">
            <Size X="2954.0000" Y="1771.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="3623.5200" Y="768.0000" />
            <Scale ScaleX="0.8800" ScaleY="0.8800" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="1.7693" Y="0.5000" />
            <PreSize X="1.4424" Y="1.1530" />
            <FileData Type="Normal" Path="Img/mg_2.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Game" ActionTag="-1152292506" Tag="920" IconVisible="True" RightMargin="2048.0000" TopMargin="1536.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="ground" ActionTag="-679265581" VisibleForFrame="False" Tag="181" IconVisible="False" LeftMargin="766.0005" RightMargin="-1282.0005" TopMargin="-396.0000" BottomMargin="-96.0000" ctype="SpriteObjectData">
                <Size X="516.0000" Y="492.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="1024.0005" Y="150.0000" />
                <Scale ScaleX="4.8000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="d_ground.png" Plist="Img/game_element.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="distance" ActionTag="-1556312040" Tag="21" IconVisible="False" LeftMargin="857.7507" RightMargin="-1108.7507" TopMargin="-1475.1288" BottomMargin="1362.1288" FontSize="100" LabelText="0.0 m" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="251.0000" Y="113.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="857.7507" Y="1418.6288" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="61" G="61" B="61" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Gameover" ActionTag="-759685544" Tag="1407" IconVisible="True" RightMargin="2048.0000" TopMargin="1536.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Gameover" ActionTag="-391689581" Tag="12" IconVisible="False" LeftMargin="-341.5000" RightMargin="-2389.5000" TopMargin="-1536.0000" ctype="SpriteObjectData">
                <Size X="2731.0000" Y="1536.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="1024.0000" Y="768.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Img/gameover/gameover_bg.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Score" ActionTag="-1556310017" Tag="317" IconVisible="False" LeftMargin="1565.0201" RightMargin="-1810.0201" TopMargin="-793.6293" BottomMargin="703.6293" FontSize="80" LabelText="12.5 m" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="245.0000" Y="90.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="1687.5201" Y="748.6293" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="PlayerName" ActionTag="1679215105" Tag="13" IconVisible="True" LeftMargin="854.9633" RightMargin="-854.9633" TopMargin="-570.7068" BottomMargin="570.7068" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="gameover_text" ActionTag="-352834172" Tag="15" IconVisible="False" LeftMargin="-655.1947" RightMargin="-613.8053" TopMargin="-334.7443" BottomMargin="152.7443" ctype="SpriteObjectData">
                    <Size X="1269.0000" Y="182.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-20.6947" Y="243.7443" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="Img/gameover/gameover_text.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="name_light" ActionTag="1086914487" Alpha="0" Tag="315" IconVisible="False" LeftMargin="-590.0000" RightMargin="-590.0000" TopMargin="-87.0000" BottomMargin="-87.0000" ctype="SpriteObjectData">
                    <Size X="1180.0000" Y="174.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="name_light.png" Plist="Img/game_element.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="name_img" ActionTag="-1018626241" Tag="314" IconVisible="False" LeftMargin="-590.0000" RightMargin="-590.0000" TopMargin="-87.0000" BottomMargin="-87.0000" ctype="SpriteObjectData">
                    <Size X="1180.0000" Y="174.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="PlistSubImage" Path="name.png" Plist="Img/game_element.plist" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Input" ActionTag="-1070742219" Tag="316" IconVisible="False" LeftMargin="-466.3357" RightMargin="-373.6643" TopMargin="-50.0000" BottomMargin="-50.0000" TouchEnable="True" FontSize="100" IsCustomSize="True" LabelText="" PlaceHolderText="Name" MaxLengthEnable="True" MaxLengthText="30" ctype="TextFieldObjectData">
                    <Size X="840.0000" Y="100.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="-466.3357" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="229" G="229" B="229" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="854.9633" Y="570.7068" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>