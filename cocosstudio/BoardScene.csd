<GameFile>
  <PropertyGroup Name="BoardScene" Type="Scene" ID="cf45579f-5a9c-475b-8567-a954232c5db6" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" Tag="136" ctype="GameNodeObjectData">
        <Size X="2731.0000" Y="1536.0000" />
        <Children>
          <AbstractNodeData Name="board_bg_1" CanEdit="False" ActionTag="893747266" Tag="138" IconVisible="False" LeftMargin="341.5000" RightMargin="341.5000" TopMargin="386.0000" BottomMargin="382.0000" ctype="SpriteObjectData">
            <Size X="1365.0000" Y="768.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1024.0000" Y="766.0000" />
            <Scale ScaleX="2.0000" ScaleY="2.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.4987" />
            <PreSize X="0.6665" Y="0.5000" />
            <FileData Type="PlistSubImage" Path="board_bg.png" Plist="Img/game_menu.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="HomeBtn" ActionTag="1720204700" Tag="150" IconVisible="False" LeftMargin="65.4461" RightMargin="1834.5540" TopMargin="56.2795" BottomMargin="1348.7205" ctype="SpriteObjectData">
            <Size X="148.0000" Y="131.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="139.4461" Y="1414.2205" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0681" Y="0.9207" />
            <PreSize X="0.0723" Y="0.0853" />
            <FileData Type="PlistSubImage" Path="board_backbtn.png" Plist="Img/game_menu.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="line_0" ActionTag="-647472510" Tag="69" IconVisible="False" LeftMargin="461.8661" RightMargin="462.1339" TopMargin="349.2589" BottomMargin="979.7411" ctype="SpriteObjectData">
            <Size X="1124.0000" Y="207.0000" />
            <Children>
              <AbstractNodeData Name="no" ActionTag="1068465280" Tag="70" IconVisible="False" LeftMargin="106.8481" RightMargin="912.1519" TopMargin="65.2346" BottomMargin="71.7654" FontSize="50" LabelText="NO.1" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="105.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="159.3481" Y="106.7654" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition X="0.1418" Y="0.5158" />
                <PreSize X="0.0934" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="name" ActionTag="-1008177516" Tag="71" IconVisible="False" LeftMargin="261.5234" RightMargin="412.4766" TopMargin="65.2347" BottomMargin="71.7653" IsCustomSize="True" FontSize="60" LabelText="" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="450.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="486.5234" Y="106.7653" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="168" G="95" B="63" />
                <PrePosition X="0.4329" Y="0.5158" />
                <PreSize X="0.4004" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="168" G="95" B="63" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="score" ActionTag="146175609" Tag="72" IconVisible="False" LeftMargin="704.2622" RightMargin="144.7378" TopMargin="64.7446" BottomMargin="72.2554" IsCustomSize="True" FontSize="60" LabelText="" HorizontalAlignmentType="HT_Right" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="275.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="841.7622" Y="107.2554" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="93" G="88" B="86" />
                <PrePosition X="0.7489" Y="0.5181" />
                <PreSize X="0.2447" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="93" G="88" B="86" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="m" ActionTag="-1585927800" Tag="73" IconVisible="False" LeftMargin="995.1431" RightMargin="76.8569" TopMargin="54.9136" BottomMargin="66.0864" FontSize="60" LabelText="m" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="52.0000" Y="86.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="1021.1431" Y="109.0864" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="93" G="88" B="86" />
                <PrePosition X="0.9085" Y="0.5270" />
                <PreSize X="0.0463" Y="0.4155" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="93" G="88" B="86" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1023.8661" Y="1083.2411" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4999" Y="0.7052" />
            <PreSize X="0.5488" Y="0.1348" />
            <FileData Type="PlistSubImage" Path="board_line.png" Plist="Img/game_menu.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="line_1" ActionTag="1475716903" Tag="104" IconVisible="False" LeftMargin="461.8661" RightMargin="462.1339" TopMargin="557.6133" BottomMargin="771.3867" ctype="SpriteObjectData">
            <Size X="1124.0000" Y="207.0000" />
            <Children>
              <AbstractNodeData Name="no" ActionTag="670347423" Tag="105" IconVisible="False" LeftMargin="100.8481" RightMargin="906.1519" TopMargin="65.2346" BottomMargin="71.7654" FontSize="50" LabelText="NO.2" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="117.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="159.3481" Y="106.7654" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition X="0.1418" Y="0.5158" />
                <PreSize X="0.1041" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="name" ActionTag="-1085059939" Tag="106" IconVisible="False" LeftMargin="261.5234" RightMargin="412.4766" TopMargin="65.2347" BottomMargin="71.7653" IsCustomSize="True" FontSize="60" LabelText="" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="450.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="486.5234" Y="106.7653" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="168" G="95" B="63" />
                <PrePosition X="0.4329" Y="0.5158" />
                <PreSize X="0.4004" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="168" G="95" B="63" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="score" ActionTag="1708559023" Tag="107" IconVisible="False" LeftMargin="704.2622" RightMargin="144.7378" TopMargin="64.7446" BottomMargin="72.2554" IsCustomSize="True" FontSize="60" LabelText="" HorizontalAlignmentType="HT_Right" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="275.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="841.7622" Y="107.2554" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="93" G="88" B="86" />
                <PrePosition X="0.7489" Y="0.5181" />
                <PreSize X="0.2447" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="93" G="88" B="86" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="m" ActionTag="1038298703" Tag="108" IconVisible="False" LeftMargin="995.1431" RightMargin="76.8569" TopMargin="54.9136" BottomMargin="66.0864" FontSize="60" LabelText="m" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="52.0000" Y="86.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="1021.1431" Y="109.0864" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="93" G="88" B="86" />
                <PrePosition X="0.9085" Y="0.5270" />
                <PreSize X="0.0463" Y="0.4155" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="93" G="88" B="86" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1023.8661" Y="874.8867" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4999" Y="0.5696" />
            <PreSize X="0.5488" Y="0.1348" />
            <FileData Type="PlistSubImage" Path="board_line.png" Plist="Img/game_menu.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="line_2" ActionTag="-1502010679" Tag="109" IconVisible="False" LeftMargin="461.8661" RightMargin="462.1339" TopMargin="765.9695" BottomMargin="563.0305" ctype="SpriteObjectData">
            <Size X="1124.0000" Y="207.0000" />
            <Children>
              <AbstractNodeData Name="no" ActionTag="622271524" Tag="110" IconVisible="False" LeftMargin="100.3481" RightMargin="905.6519" TopMargin="65.2346" BottomMargin="71.7654" FontSize="50" LabelText="NO.3" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="118.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="159.3481" Y="106.7654" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition X="0.1418" Y="0.5158" />
                <PreSize X="0.1050" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="name" ActionTag="1362053070" Tag="111" IconVisible="False" LeftMargin="261.5234" RightMargin="412.4766" TopMargin="65.2347" BottomMargin="71.7653" IsCustomSize="True" FontSize="60" LabelText="" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="450.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="486.5234" Y="106.7653" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="168" G="95" B="63" />
                <PrePosition X="0.4329" Y="0.5158" />
                <PreSize X="0.4004" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="168" G="95" B="63" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="score" ActionTag="1731194690" Tag="112" IconVisible="False" LeftMargin="704.2622" RightMargin="144.7378" TopMargin="64.7446" BottomMargin="72.2554" IsCustomSize="True" FontSize="60" LabelText="" HorizontalAlignmentType="HT_Right" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="275.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="841.7622" Y="107.2554" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="93" G="88" B="86" />
                <PrePosition X="0.7489" Y="0.5181" />
                <PreSize X="0.2447" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="93" G="88" B="86" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="m" ActionTag="1561366717" Tag="113" IconVisible="False" LeftMargin="995.1431" RightMargin="76.8569" TopMargin="54.9136" BottomMargin="66.0864" FontSize="60" LabelText="m" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="52.0000" Y="86.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="1021.1431" Y="109.0864" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="93" G="88" B="86" />
                <PrePosition X="0.9085" Y="0.5270" />
                <PreSize X="0.0463" Y="0.4155" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="93" G="88" B="86" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1023.8661" Y="666.5305" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4999" Y="0.4339" />
            <PreSize X="0.5488" Y="0.1348" />
            <FileData Type="PlistSubImage" Path="board_line.png" Plist="Img/game_menu.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="line_3" ActionTag="702192358" Tag="114" IconVisible="False" LeftMargin="461.8661" RightMargin="462.1339" TopMargin="974.3220" BottomMargin="354.6780" ctype="SpriteObjectData">
            <Size X="1124.0000" Y="207.0000" />
            <Children>
              <AbstractNodeData Name="no" ActionTag="1325172655" Tag="115" IconVisible="False" LeftMargin="99.8481" RightMargin="905.1519" TopMargin="65.2346" BottomMargin="71.7654" FontSize="50" LabelText="NO.4" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="119.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="159.3481" Y="106.7654" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition X="0.1418" Y="0.5158" />
                <PreSize X="0.1059" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="name" ActionTag="-1873933448" Tag="116" IconVisible="False" LeftMargin="261.5234" RightMargin="412.4766" TopMargin="65.2347" BottomMargin="71.7653" IsCustomSize="True" FontSize="60" LabelText="" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="450.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="486.5234" Y="106.7653" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="168" G="95" B="63" />
                <PrePosition X="0.4329" Y="0.5158" />
                <PreSize X="0.4004" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="168" G="95" B="63" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="score" ActionTag="-1555234188" Tag="117" IconVisible="False" LeftMargin="704.2622" RightMargin="144.7378" TopMargin="64.7446" BottomMargin="72.2554" IsCustomSize="True" FontSize="60" LabelText="" HorizontalAlignmentType="HT_Right" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="275.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="841.7622" Y="107.2554" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="93" G="88" B="86" />
                <PrePosition X="0.7489" Y="0.5181" />
                <PreSize X="0.2447" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="93" G="88" B="86" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="m" ActionTag="-2066687058" Tag="118" IconVisible="False" LeftMargin="995.1431" RightMargin="76.8569" TopMargin="54.9136" BottomMargin="66.0864" FontSize="60" LabelText="m" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="52.0000" Y="86.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="1021.1431" Y="109.0864" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="93" G="88" B="86" />
                <PrePosition X="0.9085" Y="0.5270" />
                <PreSize X="0.0463" Y="0.4155" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="93" G="88" B="86" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1023.8661" Y="458.1780" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4999" Y="0.2983" />
            <PreSize X="0.5488" Y="0.1348" />
            <FileData Type="PlistSubImage" Path="board_line.png" Plist="Img/game_menu.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="line_4" ActionTag="-1097126969" Tag="119" IconVisible="False" LeftMargin="461.8661" RightMargin="462.1339" TopMargin="1182.6763" BottomMargin="146.3237" ctype="SpriteObjectData">
            <Size X="1124.0000" Y="207.0000" />
            <Children>
              <AbstractNodeData Name="no" ActionTag="1219104444" Tag="120" IconVisible="False" LeftMargin="100.3481" RightMargin="905.6519" TopMargin="65.2346" BottomMargin="71.7654" FontSize="50" LabelText="NO.5" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="118.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="159.3481" Y="106.7654" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition X="0.1418" Y="0.5158" />
                <PreSize X="0.1050" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="name" ActionTag="647630242" Tag="121" IconVisible="False" LeftMargin="261.5234" RightMargin="412.4766" TopMargin="65.2347" BottomMargin="71.7653" IsCustomSize="True" FontSize="60" LabelText="" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="450.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="486.5234" Y="106.7653" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="168" G="95" B="63" />
                <PrePosition X="0.4329" Y="0.5158" />
                <PreSize X="0.4004" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="168" G="95" B="63" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="score" ActionTag="76507042" Tag="122" IconVisible="False" LeftMargin="704.2622" RightMargin="144.7378" TopMargin="64.7446" BottomMargin="72.2554" IsCustomSize="True" FontSize="60" LabelText="" HorizontalAlignmentType="HT_Right" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="275.0000" Y="70.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="841.7622" Y="107.2554" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="93" G="88" B="86" />
                <PrePosition X="0.7489" Y="0.5181" />
                <PreSize X="0.2447" Y="0.3382" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="93" G="88" B="86" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="m" ActionTag="-1671608852" Tag="123" IconVisible="False" LeftMargin="995.1431" RightMargin="76.8569" TopMargin="54.9136" BottomMargin="66.0864" FontSize="60" LabelText="m" VerticalAlignmentType="VT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="52.0000" Y="86.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="1021.1431" Y="109.0864" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="93" G="88" B="86" />
                <PrePosition X="0.9085" Y="0.5270" />
                <PreSize X="0.0463" Y="0.4155" />
                <FontResource Type="Normal" Path="font/PingFang.ttc" Plist="" />
                <OutlineColor A="255" R="93" G="88" B="86" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1023.8661" Y="249.8237" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4999" Y="0.1626" />
            <PreSize X="0.5488" Y="0.1348" />
            <FileData Type="PlistSubImage" Path="board_line.png" Plist="Img/game_menu.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="b_star_6" ActionTag="1018724145" Tag="67" IconVisible="False" LeftMargin="325.6732" RightMargin="1277.3268" TopMargin="87.5852" BottomMargin="1045.4148" ctype="SpriteObjectData">
            <Size X="445.0000" Y="403.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="548.1732" Y="1246.9148" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.2677" Y="0.8118" />
            <PreSize X="0.2173" Y="0.2624" />
            <FileData Type="PlistSubImage" Path="b_star.png" Plist="Img/game_menu.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>