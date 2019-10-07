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
        <Size X="2731.0000" Y="1536.0000" />
        <Children>
          <AbstractNodeData Name="bg" ActionTag="-849142966" Tag="20" IconVisible="False" LeftMargin="0.0020" RightMargin="-0.0020" TopMargin="-4.5000" BottomMargin="-230.5000" ctype="SpriteObjectData">
            <Size X="2731.0000" Y="1771.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1365.5020" Y="655.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.4264" />
            <PreSize X="1.0000" Y="1.1530" />
            <FileData Type="Normal" Path="Img/bg.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="mg_0" ActionTag="-1263650473" Tag="5" IconVisible="False" LeftMargin="-111.5000" RightMargin="-111.5000" TopMargin="-4.5000" BottomMargin="-230.5000" ctype="SpriteObjectData">
            <Size X="2954.0000" Y="1771.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1365.5000" Y="655.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.4264" />
            <PreSize X="1.0817" Y="1.1530" />
            <FileData Type="Normal" Path="Img/mg_1.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="mg_1" ActionTag="2123528562" Alpha="238" Tag="6" IconVisible="False" LeftMargin="2842.0000" RightMargin="-3065.0000" TopMargin="-4.5000" BottomMargin="-230.5000" ctype="SpriteObjectData">
            <Size X="2954.0000" Y="1771.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="4319.0000" Y="655.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="1.5815" Y="0.4264" />
            <PreSize X="1.0817" Y="1.1530" />
            <FileData Type="Normal" Path="Img/mg_2.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Game" CanEdit="False" ActionTag="-1152292506" Tag="920" IconVisible="True" RightMargin="2731.0000" TopMargin="1536.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="ground" ActionTag="-679265581" VisibleForFrame="False" Tag="181" IconVisible="False" LeftMargin="1107.5035" RightMargin="-1623.5035" TopMargin="-396.0000" BottomMargin="-96.0000" ctype="SpriteObjectData">
                <Size X="516.0000" Y="492.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="1365.5035" Y="150.0000" />
                <Scale ScaleX="5.4578" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="d_ground.png" Plist="Img/game_element.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="distance" ActionTag="-1556312040" Tag="21" IconVisible="False" LeftMargin="1172.1206" RightMargin="-1423.1206" TopMargin="-1503.1467" BottomMargin="1390.1467" FontSize="100" LabelText="0.0 m" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="251.0000" Y="113.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="1172.1206" Y="1446.6467" />
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
          <AbstractNodeData Name="Gameover" ActionTag="-759685544" VisibleForFrame="False" Tag="1407" IconVisible="True" RightMargin="2731.0000" TopMargin="1536.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Gameover" ActionTag="-391689581" Tag="12" IconVisible="False" RightMargin="-2731.0000" TopMargin="-1536.0000" ctype="SpriteObjectData">
                <Size X="2731.0000" Y="1536.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="1365.5000" Y="768.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Img/gameover/gameover_bg.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Score" ActionTag="-1556310017" Tag="317" IconVisible="False" LeftMargin="1907.4458" RightMargin="-2152.4458" TopMargin="-796.7422" BottomMargin="706.7422" FontSize="80" LabelText="12.5 m" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="245.0000" Y="90.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="2029.9458" Y="751.7422" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="PlayerName" ActionTag="1679215105" Tag="13" IconVisible="True" LeftMargin="1197.3892" RightMargin="-1197.3892" TopMargin="-573.8206" BottomMargin="573.8206" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Text_1" ActionTag="1136795775" Tag="46" IconVisible="False" LeftMargin="-448.8121" RightMargin="-71.1879" TopMargin="80.0926" BottomMargin="-137.0926" FontSize="50" LabelText="*請使用英文字母、數字" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="520.0000" Y="57.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-188.8121" Y="-108.5926" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
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
                  <AbstractNodeData Name="Input" ActionTag="-1070742219" Tag="316" IconVisible="False" LeftMargin="-466.3357" RightMargin="-373.6643" TopMargin="-50.0000" BottomMargin="-50.0000" TouchEnable="True" FontSize="100" IsCustomSize="True" LabelText="" PlaceHolderText="Name" MaxLengthEnable="True" MaxLengthText="8" ctype="TextFieldObjectData">
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
                <Position X="1197.3892" Y="573.8206" />
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