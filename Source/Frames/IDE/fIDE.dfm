inherited frmIDE: TfrmIDE
  Width = 1814
  Height = 772
  Align = alClient
  AutoSize = True
  Constraints.MinHeight = 600
  Constraints.MinWidth = 800
  Font.Height = -15
  Font.Name = 'Roboto'
  Font.Style = [fsBold]
  ParentFont = False
  ExplicitWidth = 1814
  ExplicitHeight = 772
  object dsIDE: TLMDDockSite
    Left = 0
    Top = 41
    Width = 1814
    Height = 731
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Manager = DockManager
    OnChange = dsIDEChange
    Align = alClient
    Constraints.MinHeight = 559
    Constraints.MinWidth = 800
    TabOrder = 0
    Layout = {
      3C3F786D6C2076657273696F6E3D22312E30223F3E0D0A3C736974656C697374
      3E0D0A20203C73697465206470693D223936222069643D2253454C465F534954
      45223E0D0A202020203C7A6F6E65206B696E643D22484F525A223E0D0A202020
      2020203C7A6F6E65206B696E643D2256455254222073697A653D223135333822
      206473697A653D22302E383536333437343338373532373834223E0D0A202020
      20202020203C7A6F6E65206B696E643D2250414E454C222073697A653D223530
      3922206473697A653D22302E3731333838343939323938373337372220697373
      706163653D2274727565222F3E0D0A20202020202020203C7A6F6E65206B696E
      643D22484F525A222073697A653D2232303422206473697A653D22302E323836
      313135303037303132363233223E0D0A202020202020202020203C7A6F6E6520
      6B696E643D225441425322206163746976657461623D2231222073697A653D22
      38353422206473697A653D22302E353537343836363331303136303433223E0D
      0A2020202020202020202020203C7A6F6E65206B696E643D2250414E454C2220
      69643D2264704D65737361676573222076697369626C653D2274727565222F3E
      0D0A2020202020202020202020203C7A6F6E65206B696E643D2250414E454C22
      2069643D2264704275696C64222076697369626C653D2274727565222F3E0D0A
      2020202020202020202020203C7A6F6E65206B696E643D2250414E454C222069
      643D226470536561726368526573756C7473222076697369626C653D22747275
      65222F3E0D0A2020202020202020202020203C7A6F6E65206B696E643D225041
      4E454C222069643D226470546F646F222076697369626C653D2274727565222F
      3E0D0A202020202020202020203C2F7A6F6E653E0D0A20202020202020202020
      3C7A6F6E65206B696E643D2250414E454C222069643D226470456469746F724B
      657973222076697369626C653D2274727565222073697A653D22363738222064
      73697A653D22302E343432353133333638393833393537222F3E0D0A20202020
      202020203C2F7A6F6E653E0D0A2020202020203C2F7A6F6E653E0D0A20202020
      20203C7A6F6E65206B696E643D2250414E454C222069643D224C4D44446F636B
      50616E656C32222076697369626C653D2266616C7365222073697A653D223735
      3422206473697A653D2230222F3E0D0A2020202020203C7A6F6E65206B696E64
      3D2256455254222073697A653D2232353822206473697A653D22302E31343336
      3532353631323437323136223E0D0A20202020202020203C7A6F6E65206B696E
      643D2250414E454C222069643D22647050726F6A656374222076697369626C65
      3D2274727565222073697A653D2233353422206473697A653D22302E34393538
      3430323636323232393632222F3E0D0A20202020202020203C7A6F6E65206B69
      6E643D2250414E454C222069643D22647050726F706572746965732220766973
      69626C653D2274727565222073697A653D2233353922206473697A653D22302E
      353034313539373333373737303338222F3E0D0A2020202020203C2F7A6F6E65
      3E0D0A202020203C2F7A6F6E653E0D0A20203C2F736974653E0D0A3C2F736974
      656C6973743E0D0A}
    object dpBuild: TLMDDockPanel
      Left = 6
      Top = 521
      Width = 854
      Height = 182
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Images = imgBuildNodes
      ImageIndex = 3
      ShowHeaderImage = hiShow
      ParentBackground = False
      TabOrder = 8
      Caption = 'BUILD'
      object tvBuild: TElXTree
        Left = 0
        Top = 23
        Width = 854
        Height = 159
        Cursor = crArrow
        Hint = ''
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        PlusPosition = vaMiddle
        BorderColorWindow = clWindow
        UseThemeForSelection = True
        ActiveBorderType = fbtFlat
        Align = alClient
        AutoExpand = True
        Style.FontSize = 9
        Style.FontStyles = [fsBold]
        Style.FontName = 'Roboto'
        CustomPlusMinus = True
        DoInplaceEdit = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Roboto'
        Font.Style = [fsBold]
        FullRowSelect = False
        HeaderHeight = 19
        HeaderSections.Data = {
          F1FFFFFF010000000000000000000000FFFFFFFF000001010100000000000000
          00000000102700000000000010DCE6020000000001000000FFFFFFFF00000100
          0000000000000000000100000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000020000000000020000000000
          0000000000000000}
        HeaderSections.Cells = {0000000001000000010000000000}
        HideFocusRect = True
        HideHintOnMove = False
        HorzScrollBarStyles.Width = 17
        Images = imgBuildNodes
        ItemIndent = 18
        LineHeight = 18
        LinesColor = clBtnShadow
        MinusPicture.Data = {
          EE000000424DEE0000000000000076000000280000000F0000000F0000000100
          04000000000078000000C40E0000C40E00001000000010000000000000004040
          4000FFFFFF000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000001110000000000001121100
          0000000011222110000000011221221100000011221112211000011221101122
          1100012211000112210001211000001121000111000000011100000000000000
          000000000000000000000000000000000000}
        MultiSelect = False
        ParentFont = False
        ParentShowHint = False
        PlusMinusTransparent = True
        PlusPicture.Data = {
          EE000000424DEE0000000000000076000000280000000F0000000F0000000100
          04000000000078000000C30E0000C30E00001000000010000000000000004040
          4000FFFFFF000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000111100000000000012211000000000001122110000000000011221100
          0000000001122110000000000011221100000000000112210000000000112211
          0000000001122110000000001122110000000001122110000000000122110000
          000000011110000000000000000000000000}
        ShowHint = False
        ShowLeafButton = False
        ShowLines = False
        ShowRoot = True
        SortSection = -1
        StoragePath = '\Tree'
        TabOrder = 0
        TabStop = True
        HotTrack = False
        UnderlineTracked = False
        VertScrollBarStyles.ShowTrackHint = True
        VertScrollBarStyles.Width = 17
        UseSystemHintColors = True
        BackGroundColor = clBtnFace
        FixedTopRowNum = 0
        FixedBottomRowNum = 0
        FixedColNum = 1
        GutterWidth = 0
      end
    end
    object dpEditorKeys: TLMDDockPanel
      Left = 866
      Top = 521
      Width = 678
      Height = 204
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Images = imgProjectNodes
      ImageIndex = 24
      ShowHeaderImage = hiShow
      ParentBackground = False
      TabOrder = 11
      Caption = 'EDITOR KEYS'
      object mbKeys: TMemo
        Left = 0
        Top = 23
        Width = 678
        Height = 181
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = []
        Lines.Strings = (
          '')
        ParentFont = False
        ParentShowHint = False
        ReadOnly = True
        ScrollBars = ssBoth
        ShowHint = False
        TabOrder = 0
      end
    end
    object dpMessages: TLMDDockPanel
      Left = 6
      Top = 521
      Width = 854
      Height = 182
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Images = imgProjectNodes
      ImageIndex = 25
      ShowHeaderImage = hiShow
      ParentBackground = False
      TabOrder = 5
      Caption = 'MESSAGES'
      object memMessages: TMemo
        Left = 0
        Top = 23
        Width = 854
        Height = 159
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Consolas'
        Font.Style = [fsBold]
        Lines.Strings = (
          '')
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
    object dpProject: TLMDDockPanel
      Left = 1550
      Top = 6
      Width = 258
      Height = 354
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Images = vilProject
      ImageIndex = 4
      Buttons = [pbPin, pbMaximize]
      ShowHeaderImage = hiShow
      ParentBackground = False
      TabOrder = 6
      Caption = 'PROJECT'
      object Panel1: TPanel
        Left = 0
        Top = 23
        Width = 258
        Height = 331
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alClient
        BevelOuter = bvNone
        Padding.Left = 1
        Padding.Top = 1
        Padding.Right = 1
        Padding.Bottom = 1
        TabOrder = 0
        object tbrProject: TToolBar
          Left = 1
          Top = 1
          Width = 256
          Height = 26
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          AutoSize = True
          ButtonHeight = 24
          ButtonWidth = 24
          Constraints.MaxHeight = 26
          Constraints.MinHeight = 26
          DrawingStyle = dsGradient
          Images = vilProject
          TabOrder = 0
          object tbnProjectCollapseAll: TToolButton
            Left = 0
            Top = 0
            Hint = 'Collapse All'
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Caption = 'tbnProjectCollapseAll'
            ImageIndex = 1
            ImageName = 'tv collapse'
            ParentShowHint = False
            ShowHint = True
            OnClick = tbnProjectCollapseAllClick
          end
          object tbnProjectShowFolders: TToolButton
            Left = 24
            Top = 0
            Hint = 'Show Folders'
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            ImageIndex = 4
            ImageName = 'tv showfolders'
            ParentShowHint = False
            ShowHint = True
            OnClick = tbnProjectShowFoldersClick
          end
          object tbnProjectExpandAll: TToolButton
            Left = 48
            Top = 0
            Hint = 'Expand All'
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            ImageIndex = 0
            ImageName = 'tv expand'
            ParentShowHint = False
            ShowHint = True
            OnClick = tbnProjectExpandAllClick
          end
          object tbnProjectZ1: TToolButton
            Left = 72
            Top = 0
            Width = 8
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Caption = 'tbnProjectZ1'
            ImageIndex = 2
            ImageName = 'tv showlines'
            Style = tbsSeparator
          end
          object tbnProjectShowLines: TToolButton
            Left = 80
            Top = 0
            Hint = 'Show Lines'
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Grouped = True
            ImageIndex = 2
            ImageName = 'tv showlines'
            ParentShowHint = False
            ShowHint = True
            Style = tbsCheck
            OnClick = tbnProjectShowLinesClick
          end
          object tbnProjectHideLines: TToolButton
            Left = 104
            Top = 0
            Hint = 'Hide Lines'
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Grouped = True
            ImageIndex = 3
            ImageName = 'tv hidelines'
            ParentShowHint = False
            ShowHint = True
            Style = tbsCheck
            OnClick = tbnProjectHideLinesClick
          end
        end
        object tvProject: TElXTree
          Left = 1
          Top = 27
          Width = 256
          Height = 303
          Hint = ''
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          PlusPosition = vaMiddle
          BorderColorWindow = clWindow
          ActiveBorderType = fbtNone
          Align = alClient
          Style.ParentColors = False
          Style.TextColor = 3355443
          Style.FontSize = 9
          Style.FontStyles = []
          Style.FontName = 'Roboto'
          CustomPlusMinus = True
          DoInplaceEdit = False
          Flat = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 3355443
          Font.Height = -12
          Font.Name = 'Roboto'
          Font.Style = []
          HeaderHeight = 19
          HeaderSections.Data = {
            F1FFFFFF010000000000000000000000FFFFFFFF000001010100000000000000
            000000001027000000000000D0C6A9240000000001000000FFFFFFFF00000100
            0000000000000000000100000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000020000000000020000000000
            0000000000000000}
          HeaderSections.Cells = {0000000001000000010000000000}
          HorzScrollBarStyles.Width = 17
          HorzScrollBarStyles.ThemeGlobalMode = True
          Images = imgProjectNodes
          ItemIndent = 18
          LineHeight = 18
          MinusPicture.Data = {
            EE000000424DEE0000000000000076000000280000000F0000000F0000000100
            04000000000078000000C40E0000C40E00001000000010000000000000004040
            4000FFFFFF000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000001110000000000001121100
            0000000011222110000000011221221100000011221112211000011221101122
            1100012211000112210001211000001121000111000000011100000000000000
            000000000000000000000000000000000000}
          ParentFont = False
          PlusMinusTransparent = True
          PlusPicture.Data = {
            EE000000424DEE0000000000000076000000280000000F0000000F0000000100
            04000000000078000000C30E0000C30E00001000000010000000000000004040
            4000FFFFFF000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000111100000000000012211000000000001122110000000000011221100
            0000000001122110000000000011221100000000000112210000000000112211
            0000000001122110000000001122110000000001122110000000000122110000
            000000011110000000000000000000000000}
          PopupMenu = popProject
          ShowLeafButton = False
          SortSection = -1
          StoragePath = '\Tree'
          TabOrder = 1
          TabStop = True
          UseCustomScrollBars = False
          VertScrollBarStyles.ShowTrackHint = True
          VertScrollBarStyles.Width = 17
          VertScrollBarStyles.ThemeGlobalMode = True
          ParentThemeMode = False
          ThemeGlobalMode = True
          TextColor = 3355443
          OnItemSelectedChange = tvProjectItemSelectedChange
          OnDblClick = tvProjectDblClick
          FixedTopRowNum = 0
          FixedBottomRowNum = 0
          FixedColNum = 1
          GutterWidth = 0
        end
      end
    end
    object dpProperties: TLMDDockPanel
      Left = 1550
      Top = 366
      Width = 258
      Height = 359
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Images = imgBuildNodes
      ImageIndex = 9
      Buttons = [pbPin, pbMaximize]
      ShowHeaderImage = hiShow
      ParentBackground = False
      TabOrder = 10
      Caption = 'PROPERTIES'
      object Splitter1: TSplitter
        Left = 0
        Top = 316
        Width = 258
        Height = 3
        Cursor = crVSplit
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alBottom
        AutoSnap = False
        MinSize = 40
        ResizeStyle = rsUpdate
        ExplicitTop = 225
        ExplicitWidth = 63
      end
      object lmdProperties: TLMDSimplePropInspector
        Left = 0
        Top = 23
        Width = 258
        Height = 293
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        PropKinds = [pkProperties, pkReadOnly]
        SortType = stNone
        ArrangeKind = akByCategory
        GridVisible = False
        GutterVisible = True
        CursorVisible = True
        SelectionStyle = ssFlat
        CategoryFont.Charset = DEFAULT_CHARSET
        CategoryFont.Color = clHighlightText
        CategoryFont.Height = -12
        CategoryFont.Name = 'Roboto'
        CategoryFont.Style = [fsBold]
        Splitter = 100
        ExpandedCategories = True
        Align = alClient
        Color = clWindow
        Constraints.MinWidth = 200
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Roboto'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = lmdPropertiesClick
      end
      object Panel2: TPanel
        Left = 0
        Top = 319
        Width = 258
        Height = 40
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alBottom
        BevelOuter = bvNone
        Constraints.MinHeight = 40
        Padding.Left = 3
        Padding.Top = 3
        Padding.Right = 3
        Padding.Bottom = 3
        ParentBackground = False
        TabOrder = 1
        object lblPropertyInfo: TLabel
          Left = 3
          Top = 3
          Width = 252
          Height = 34
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Align = alClient
          Caption = 'Property information'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Roboto'
          Font.Style = []
          ParentFont = False
          Transparent = True
          WordWrap = True
          ExplicitWidth = 112
          ExplicitHeight = 14
        end
      end
    end
    object dpSearchResults: TLMDDockPanel
      Left = 6
      Top = 521
      Width = 854
      Height = 182
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Images = imgProjectNodes
      ImageIndex = 28
      ShowHeaderImage = hiShow
      ParentBackground = False
      TabOrder = 7
      Caption = 'SEARCH RESULTS'
    end
    object dpTodo: TLMDDockPanel
      Left = 6
      Top = 521
      Width = 854
      Height = 182
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Images = imgBuildNodes
      ImageIndex = 11
      ShowHeaderImage = hiShow
      ParentBackground = False
      TabOrder = 9
      Caption = 'TODO'
    end
    object LMDDockPanel2: TLMDDockPanel
      Left = 0
      Top = 0
      Width = 754
      Height = 719
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      PanelVisible = False
      Enabled = False
      ParentBackground = False
      TabOrder = 4
      Caption = 'dpEditors'
    end
  end
  object panToolbar: TPanel
    Left = 0
    Top = 0
    Width = 1814
    Height = 41
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Align = alTop
    AutoSize = True
    BevelOuter = bvNone
    TabOrder = 1
    object tbrMain: TToolBar
      Left = 0
      Top = 0
      Width = 552
      Height = 41
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Align = alLeft
      AutoSize = True
      ButtonHeight = 40
      ButtonWidth = 40
      EdgeInner = esNone
      EdgeOuter = esNone
      Flat = False
      Images = vilToolbar
      TabOrder = 0
      Transparent = False
      StyleElements = [seFont, seClient]
      Wrapable = False
      object ToolButton3: TToolButton
        Left = 0
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actFileNewSprite
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton7: TToolButton
        Left = 40
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actFileNewObject
        ParentShowHint = False
        ShowHint = True
      end
      object btnFileNewImage: TToolButton
        Left = 80
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actFileNewTile
        ParentShowHint = False
        ShowHint = True
      end
      object btnFileNewTileCustom: TToolButton
        Left = 120
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actFileNewTileCustom
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton1: TToolButton
        Left = 160
        Top = 0
        Width = 8
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Caption = 'ToolButton1'
        ImageIndex = 7
        ImageName = 'paste_plain'
        Style = tbsSeparator
      end
      object ToolButton4: TToolButton
        Left = 168
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actEditUndo
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton5: TToolButton
        Left = 208
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actEditRedo
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton6: TToolButton
        Left = 248
        Top = 0
        Width = 8
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Caption = 'ToolButton6'
        ImageIndex = 1
        ImageName = 'folder'
        Style = tbsSeparator
      end
      object btnEditCopy: TToolButton
        Left = 256
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actEditCopy
        ParentShowHint = False
        ShowHint = True
      end
      object btnEditCut: TToolButton
        Left = 296
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actEditCut
        ParentShowHint = False
        ShowHint = True
      end
      object btnEditPaste: TToolButton
        Left = 336
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actEditPaste
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton11: TToolButton
        Left = 376
        Top = 0
        Width = 8
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Caption = 'ToolButton11'
        ImageIndex = 9
        ImageName = 'find'
        Style = tbsSeparator
      end
      object ToolButton10: TToolButton
        Left = 384
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actEditZoomIn
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton12: TToolButton
        Left = 424
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actEditZoomOut
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton13: TToolButton
        Left = 464
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actEditZoomReset
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton2: TToolButton
        Left = 504
        Top = 0
        Width = 8
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Caption = 'ToolButton2'
        ImageName = 'resize_picture'
        Style = tbsSeparator
      end
      object btnBuildRun: TToolButton
        Left = 512
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actGameRun
        ParentShowHint = False
        ShowHint = True
      end
    end
    object tbrSettings: TToolBar
      Left = 1726
      Top = 0
      Width = 88
      Height = 41
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Align = alRight
      AutoSize = True
      ButtonHeight = 40
      ButtonWidth = 40
      Images = vilToolbar
      TabOrder = 1
      object btnEditorHelp: TToolButton
        Left = 0
        Top = 0
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actEditorHelp
        ParentShowHint = False
        ShowHint = True
        Visible = False
      end
      object ToolButton14: TToolButton
        Left = 40
        Top = 0
        Width = 8
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Caption = 'ToolButton14'
        ImageIndex = 6
        ImageName = 'cut'
        Style = tbsSeparator
        Visible = False
      end
      object btnSettings: TToolButton
        Left = 48
        Top = 0
        Hint = 'Application Settings'
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Action = actSettings
        ParentShowHint = False
        ShowHint = True
      end
    end
  end
  object actActions: TActionList
    Images = vilToolbar
    State = asSuspended
    Left = 216
    Top = 88
    object actFileProjectSave: TAction
      Category = 'File'
      Caption = '&Save'
      Hint = 'Save project'
      ImageIndex = 2
      ImageName = 'disk'
      ShortCut = 16467
      OnExecute = actFileProjectSaveExecute
    end
    object actFileProjectClose: TAction
      Category = 'File'
      Caption = '&Close'
      Hint = 'Close project'
      ImageIndex = 8
      ImageName = 'cross'
      ShortCut = 16499
      OnExecute = actFileProjectCloseExecute
    end
    object actEditCopy: TAction
      Category = 'Edit'
      Caption = '&Copy'
      Hint = 'Copy'
      ImageIndex = 5
      ImageName = 'page_white_copy'
      ShortCut = 16451
      OnExecute = actEditCopyExecute
    end
    object actEditCut: TAction
      Category = 'Edit'
      Caption = 'Cu&t'
      Hint = 'Cut'
      ImageIndex = 6
      ImageName = 'cut'
      ShortCut = 16472
      OnExecute = actEditCutExecute
    end
    object actEditPaste: TAction
      Category = 'Edit'
      Caption = '&Paste'
      Hint = 'Paste'
      ImageIndex = 7
      ImageName = 'paste_plain'
      ShortCut = 16470
      OnExecute = actEditPasteExecute
    end
    object actHelp: TAction
      Category = 'Help'
      Caption = '&Help'
      ImageIndex = 15
      ImageName = 'help'
      ShortCut = 112
    end
    object actHelpGettingStarted: TAction
      Category = 'Help'
      Caption = '&Getting Started'
      ShortCut = 16496
    end
    object actHelpKeymapReference: TAction
      Category = 'Help'
      Caption = '&Keymap Reference'
    end
    object actHelpTipOfTheDay: TAction
      Category = 'Help'
      Caption = '&Tip of the day...'
    end
    object actHelpCheckForUpdates: TAction
      Category = 'Help'
      Caption = 'Check for Updates...'
    end
    object actHelpAbout: TAction
      Category = 'Help'
      Caption = '&About'
      OnExecute = actHelpAboutExecute
    end
    object actEditUndo: TAction
      Category = 'Edit'
      Caption = '&Undo'
      Enabled = False
      Hint = 'Undo'
      ImageIndex = 3
      ImageName = 'arrow_undo'
      ShortCut = 16474
      OnExecute = actEditUndoExecute
    end
    object actEditRedo: TAction
      Category = 'Edit'
      Caption = '&Redo'
      Enabled = False
      Hint = 'Redo'
      ImageIndex = 4
      ImageName = 'arrow_redo'
      ShortCut = 24666
      OnExecute = actEditRedoExecute
    end
    object actEditZoomIn: TAction
      Category = 'Edit'
      Caption = 'Zoom &In'
      Hint = 'Zoom In'
      ImageIndex = 11
      ImageName = 'zoom_in'
      ShortCut = 16571
      OnExecute = actEditZoomInExecute
    end
    object actEditZoomOut: TAction
      Category = 'Edit'
      Caption = 'Zoom &Out'
      Hint = 'Zoom Out'
      ImageIndex = 12
      ImageName = 'zoom_out'
      ShortCut = 16573
      OnExecute = actEditZoomOutExecute
    end
    object actEditZoomReset: TAction
      Category = 'Edit'
      Caption = 'Zoom &Reset'
      Hint = 'Zoom Reset'
      ImageIndex = 13
      ImageName = 'zoom_actual'
      ShortCut = 16432
      OnExecute = actEditZoomResetExecute
    end
    object actEditFind: TAction
      Category = 'Edit'
      Caption = 'Find...'
      Hint = 'Search the active document'
      ImageIndex = 9
      ImageName = 'find'
      ShortCut = 16454
      OnExecute = actEditFindExecute
    end
    object actEditFindNext: TAction
      Category = 'Edit'
      Caption = 'Find Next'
      Hint = 'Search the document for the next match'
      ShortCut = 114
      OnExecute = actEditFindNextExecute
    end
    object actEditReplace: TAction
      Category = 'Edit'
      Caption = 'Replace'
      ImageIndex = 10
      ImageName = 'text_replace'
      ShortCut = 16456
      OnExecute = actEditReplaceExecute
    end
    object actEditFindPrevious: TAction
      Category = 'Edit'
      Caption = 'Find Previous'
      ShortCut = 8306
      OnExecute = actEditFindPreviousExecute
    end
    object actFileProjectOpen: TAction
      Category = 'File'
      Caption = 'Open Project...'
      Hint = 'Open an existing project.'
      ImageIndex = 1
      ImageName = 'folder'
      ShortCut = 16463
      OnExecute = actFileProjectOpenExecute
    end
    object actFileNewImageDefault: TAction
      Category = 'File'
      Caption = 'New Image... (Default Size)'
      Hint = 'New Image (Default Size)'
      ImageIndex = 17
      ImageName = 'image_add'
      OnExecute = actFileNewImageDefaultExecute
    end
    object actDeleteAsset: TAction
      Category = 'Edit'
      Caption = 'Delete Image'
      ImageIndex = 8
      ImageName = 'cross'
      ShortCut = 8238
      OnExecute = actDeleteAssetExecute
    end
    object actSettings: TAction
      Caption = 'Settings...'
      Hint = 'Show the application settings dialog'
      ImageIndex = 16
      ImageName = 'cog'
      ShortCut = 24698
      OnExecute = actSettingsExecute
    end
    object actEditorHelp: TAction
      Caption = 'Help'
      Hint = 'Show Editor Help'
      ImageIndex = 15
      ImageName = 'help'
      OnExecute = actEditorHelpExecute
    end
    object actFileNewTileCustom: TAction
      Category = 'File'
      Caption = 'New Tile Image... (Custom Size)'
      Hint = 'New Tile Image (Custom Size)'
      ImageIndex = 21
      ImageName = 'tile_add_custom'
      ShortCut = 24654
      OnExecute = actFileNewTileCustomExecute
    end
    object actViewBuildResults: TAction
      Category = 'View'
      AutoCheck = True
      Caption = 'Build Results'
      Checked = True
      ShortCut = 49218
      OnExecute = actViewBuildResultsExecute
    end
    object actViewMessages: TAction
      Category = 'View'
      AutoCheck = True
      Caption = 'Messages'
      Checked = True
      ShortCut = 49229
      OnExecute = actViewMessagesExecute
    end
    object actViewSearchResults: TAction
      Category = 'View'
      AutoCheck = True
      Caption = 'Search Results'
      Checked = True
      ShortCut = 49235
      OnExecute = actViewSearchResultsExecute
    end
    object actViewTodo: TAction
      Category = 'View'
      AutoCheck = True
      Caption = 'Todo'
      Checked = True
      ShortCut = 49236
      OnExecute = actViewTodoExecute
    end
    object actViewEditorKeys: TAction
      Category = 'View'
      AutoCheck = True
      Caption = 'Editor Keys'
      Checked = True
      ShortCut = 49221
      OnExecute = actViewEditorKeysExecute
    end
    object actGameRun: TAction
      Caption = 'Run...'
      Hint = 'Build and Run the game'
      ImageIndex = 14
      ImageName = 'control_play_blue'
      SecondaryShortCuts.Strings = (
        'F5')
      ShortCut = 120
      OnExecute = actGameRunExecute
    end
    object actFileNewTile: TAction
      Tag = 2
      Category = 'File'
      Caption = 'New Tile (Default Size)'
      Hint = 'New Tile (Default Size)'
      ImageIndex = 20
      ImageName = 'tile_add'
      ShortCut = 24660
      OnExecute = actFileNewTileExecute
    end
    object actFileNewObject: TAction
      Category = 'File'
      Caption = 'New Object (Default Size)'
      Hint = 'New Object (Default Size)'
      ImageIndex = 19
      ImageName = 'object_add'
      ShortCut = 24655
      OnExecute = actFileNewObjectExecute
    end
    object actFileNewSprite: TAction
      Tag = 1
      Category = 'File'
      Caption = 'New Sprite (Default Size)'
      Hint = 'New Sprite (Default Size)'
      ImageIndex = 18
      ImageName = 'sprite_add'
      ShortCut = 24659
      OnExecute = actFileNewSpriteExecute
    end
    object actEditDuplicateImage: TAction
      Category = 'Edit'
      Caption = 'Duplicate Image'
      ImageIndex = 5
      ImageName = 'page_white_copy'
      OnExecute = actEditDuplicateImageExecute
    end
    object actEditSplitIntoTiles: TAction
      Category = 'Edit'
      Caption = 'Split into Single Tiles'
      Hint = 'Split the tile into separate single tiles.'
      ImageIndex = 20
      ImageName = 'tile_add'
      OnExecute = actEditSplitIntoTilesExecute
    end
  end
  object mnuMain: TMainMenu
    Images = vilToolbar
    Left = 28
    Top = 88
    object mnuFile: TMenuItem
      Caption = '&Project'
      object New1: TMenuItem
        Caption = 'New'
        object NewSpriteDefaultSize1: TMenuItem
          Action = actFileNewSprite
        end
        object NewObjectDefaultSize1: TMenuItem
          Action = actFileNewObject
        end
        object NewTileDefaultSize1: TMenuItem
          Action = actFileNewTile
        end
        object N6: TMenuItem
          Caption = '-'
        end
        object NewTileImageCustomSize1: TMenuItem
          Action = actFileNewTileCustom
        end
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object mnuFileOpenProject: TMenuItem
        Action = actFileProjectOpen
      end
      object mnuFileMru: TMenuItem
        Caption = 'Reopen'
      end
      object mnuFileSave: TMenuItem
        Action = actFileProjectSave
      end
      object mnuFileClose: TMenuItem
        Action = actFileProjectClose
      end
    end
    object mnuEdit: TMenuItem
      Caption = '&Edit'
      object mnuEditUndo: TMenuItem
        Action = actEditUndo
      end
      object mnuEditRedo: TMenuItem
        Action = actEditRedo
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object mnuEditCopy: TMenuItem
        Action = actEditCopy
      end
      object mnuEditCut: TMenuItem
        Action = actEditCut
      end
      object mnuEditPaste: TMenuItem
        Action = actEditPaste
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object Settings1: TMenuItem
        Action = actSettings
      end
    end
    object mnuView: TMenuItem
      Caption = '&View'
      object mnuViewBuildResults: TMenuItem
        Action = actViewBuildResults
        AutoCheck = True
      end
      object mnuViewSearchResults: TMenuItem
        Action = actViewSearchResults
        AutoCheck = True
      end
      object mnuViewMessages: TMenuItem
        Action = actViewMessages
        AutoCheck = True
      end
      object mnuViewTodo: TMenuItem
        Action = actViewTodo
        AutoCheck = True
      end
      object mnuViewEditorKeys: TMenuItem
        Action = actViewEditorKeys
        AutoCheck = True
      end
    end
    object mnuGame: TMenuItem
      Caption = '&Game'
      object mnuRun: TMenuItem
        Action = actGameRun
        Caption = 'Run'
      end
    end
    object mnuTools: TMenuItem
      Caption = 'Tools'
      Visible = False
      object mnuToolMachineDefinition: TMenuItem
        Caption = 'Machine Definition Editor...'
      end
      object mnuToolKeyboardLayout: TMenuItem
        Caption = 'Keyboard Layout Editor...'
      end
      object mnuToolGraphicsMode: TMenuItem
        Caption = 'Graphics Mode Editor...'
      end
    end
    object mnuHelp: TMenuItem
      Caption = '&Help'
      object mnuHelpHelp: TMenuItem
        Action = actHelp
      end
      object mnuHelpGettingStarted: TMenuItem
        Action = actHelpGettingStarted
      end
      object mnuHelpKeymapReference: TMenuItem
        Action = actHelpKeymapReference
        Visible = False
      end
      object mnuSpecialThanks: TMenuItem
        Caption = 'Special Thanks...'
        Enabled = False
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object mnuHelpCheckforUpdates: TMenuItem
        Action = actHelpCheckForUpdates
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object mnuHelpAbout: TMenuItem
        Action = actHelpAbout
        Caption = '&About...'
      end
    end
  end
  object DockManager: TLMDDockManager
    StyleName = 'VCLStyle'
    Left = 314
    Top = 88
  end
  object imgProjectNodes: TImageList
    ColorDepth = cd32Bit
    Left = 118
    Top = 184
    Bitmap = {
      494C01011D003000040010001000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000008000000001002000000000000080
      0000000000000000000000000000000000000000002300000033000000330000
      0033000000330000003300000023000000000000000000000023000000330000
      0033000000330000003300000033000000230000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003F3F3DC0757371FF6F6C6BFF6C69
      68FF686664FF656261FF333130C000000000000000003F3F3DC0757371FF6F6C
      6BFF6C6968FF686664FF656261FF333130C00000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000797775FF817D7CFF9C9996FF8985
      83FF706E6BFF585655FF5F5C5BFF0000000000000000797775FF817D7CFF9C99
      96FF898583FF706E6BFF585655FF605D5CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000767472FFCFCFCFFFD9D7D6FFD0CF
      CEFFC8C8C7FFC3C1C1FF5D5958FF0000000000000000767472FFD0CFCFFFD9D7
      D6FFD0CFCEFFC8C8C7FFC3C1C1FF5D5A59FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000757371FFB3B1AFFFCAC9C7FFB0AE
      ADFF91908EFF747371FF5D5958FF0000003300000033767472FFB3B1AFFFCAC9
      C7FFB0AEADFF91908EFF747471FF5E5B5AFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000757371FFB3B1AFFFCAC9C7FFB1AE
      AEFF939290FF767573FF5D5958FF797775FF63615FFF767472FFB3B1AFFFCAC9
      C7FFB1AEAEFF939290FF767573FF5F5C5BFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000757371FFB3B0AEFFCAC9C7FFB0AD
      ADFF91908EFF747371FF5A5756FF757371FF605E5CFF757371FFB3B1AFFFCAC9
      C7FFB0ADADFF91908EFF747472FF5E5B5AFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000767371FFDEDDDDFFEBEBE9FFDBDA
      D9FFCAC9C8FFBBBAB9FF565352FFD6D5D3FF8C8B89FF747270FFDEDDDCFFEBEB
      E9FFDBDAD9FFCAC9C8FFBCBCBBFF5D5A59FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000797775FF6E6C6AFF656160FF5F5C
      5BFF5D5B59FF5D5959FF1A1A1A9BD3D2D0FF8A8987FF2423239B6B6967FF6360
      5FFF615E5DFF605E5CFF605D5CFF2A2828A80000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000767372FFBCBAB8FFCDCB
      CAFFA5A3A2FF7D7B7AFF585554FFD6D5D3FF8C8C89FF757271FFBCBAB7FFCCCA
      C9FFA4A2A1FF7D7B7AFF5E5B5AFF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000767372FFB9B7B5FFC9C7
      C6FFA2A09FFF7C7A79FF5B5757FF767371FF605E5CFF767372FFB9B8B5FFC9C7
      C6FFA2A09FFF7D7B7AFF5F5C5BFF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000777473FFBDBBB9FFCECC
      CBFFA5A3A2FF7D7B7AFF5D5A59FF7A7876FF63615FFF787574FFBCBBB8FFCECC
      CBFFA6A4A3FF807D7CFF5F5C5BFF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000383736AE706D6CFF6865
      64FF635F5EFF615D5CFF252423AA00000000000000002F2E2DAA6E6B6AFF6865
      64FF666362FF646160FF2E2C2CAE000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000337774
      73FFCBCAC7FF9B9A99FF615D5CFF0000000000000000777473FFCAC8C6FF9897
      96FF5F5C5BFF0000003300000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000797875FF908D
      8CFF908E8CFF646360FF605D5CFF0000000000000000787674FF8E8B8AFF918F
      8DFF676563FF625F5EFF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007A7876FF7270
      6EFF6C6A68FF686564FF615E5DFF00000000000000007A7876FF72706EFF6C6A
      68FF686564FF625F5EFF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002300000000000000000000000000000000000000220000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000003300000022000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002300000000000000000000003000000033000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      003300000033000000330000003300000023000000005C5C5BC0B0B0ADFFAEAE
      ACFFAEAEACFFAFAFACFFAEAEACFFAEAEACFFAEAEACFFAEAEACFFAEAEACFFAEAE
      ACFFAFAFADFF5C5C5BC0000000000000000000000000000000004B4315B99C8D
      2BFF9C8C2BFF9C8C2BFF9C8C2BFF9C8C2BFF9C8C2BFF9C8C2BFF9C8C2BFF9C8C
      2BFF9C8C2BFF9C8D2BFF4B4315B900000000000000006E4A15C0D18F27FFD08E
      25FFD08E24FFD08E24FFD08E25FFD08E25FFD08E25FFD08E24FFD08E24FFD08E
      25FFD18F27FF6E4A15C000000000000000008E877AF29E9688FF9D9587FF9D95
      87FF9D9487FF9D9486FF9D9486FF9D9486FF9D9486FF9D9486FF9D9486FF9D94
      87FF9D9587FF9D9587FF9E9688FF534E48C000000000B0B0ADFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFB0B0ADFF000000000000000000000000000000009C8D2BFFC7C5
      53FFC2C04EFFC2BF4CFFC0BD47FFC2BF4CFFC2C04EFFC2BF4CFFC0BD47FFC2BF
      4CFFC2C04EFFC7C553FF9C8D2BFF0000000000000000D18F27FFFFAD60FFFEA7
      55FFFEA44FFFFEA44EFFFEA550FFFEA652FFFEA550FFFEA44EFFFEA44FFFFEA7
      55FFFFAD60FFD18F27FF00000000000000009E9688FFCAC5C2FFC7C2BEFFC7C2
      BEFFC6C1BDFFC5C0BCFFC5C0BBFFC5C0BBFFC5C0BBFFC5C0BBFFC5C0BCFFC6C1
      BDFFC7C2BEFFC7C2BEFFCAC5C2FF9E9688FF00000000AEAEABFFFFFFFFFFFFFF
      FFFF818181FFB8B8B8FFB6B7B7FFB4B4B5FFFFFFFFFF818181FFB5B5B5FFFFFF
      FFFFFFFFFFFFAEAEABFF000000000000000000000000000000009C8C2BFFFF25
      00FFBDB84AFFFF2500FFBDB84AFFFF2500FFFF2500FFFF2500FFBDB84AFFFF25
      00FFFF2500FFC7C654FF9C8C2BFF0000000000000000D08E25FFFFAE60FFF7A0
      46FFFFFFFFFFFDE2C9FFF9B773FFF9B975FFF9B773FFFDE2C9FFFFFFFFFFF7A0
      46FFFFAE60FFD08E25FF00000000000000009D9487FFC9C6C1FFF6F8FAFFAFA8
      9DFFF5F6F9FFF3F4F6FFF3F4F6FFF3F4F6FFF3F4F6FFF3F4F6FFF3F4F6FFF5F6
      F8FFAFA89DFFF6F8FAFFC9C6C1FF9D9487FF00000000ADADABFFFFFFFFFFFEFD
      FDFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDFB
      FBFFFFFFFFFFADADABFF000000000000000000000000000000009C8C2BFFFF25
      00FFB9B446FFFF2500FFB9B446FFFF2500FFB9B446FFFF2500FFB9B446FFFF25
      00FFB9B446FFFF2500FF9C8C2BFF0000000000000000D08E25FFFFB165FFF29D
      42FFF9D3AAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9D3AAFFF29D
      42FFFFB165FFD08E25FF00000000000000009D9487FFCDCAC4FFAAA497FFACA5
      98FFACA599FFAAA497FFABA498FFAAA497FFABA498FFAAA497FFABA498FFAAA4
      97FFAAA397FFAAA396FFCDC9C4FF9D9487FF00000000ADADABFFFFFFFFFFFBFB
      FBFF828282FFB7B6B6FFB5B3B3FFFEFEFEFF828383FFB7B6B6FFB3B2B2FFF9F9
      F9FFFFFFFFFFADADABFF000000000000000000000000000000009B8C2AFFFF25
      00FFFF2500FFFF2500FFB6B043FFFF2500FFB6B043FFB3AC38FFB6B043FFFF25
      00FFB6B043FFFF2500FF9B8C2AFF0000000000000000D08E25FFFFB56AFFEF9D
      41FFF1A652FFFFFFFFFFF79D42FFE79028FFD88C21FFFFFFFFFFF1A652FFEF9D
      41FFFFB56AFFD08E25FF00000000000000009C9486FFCFCDC6FFF5F6F9FFF7F8
      FAFFA9A296FFF8FAFDFFA9A396FFF8FAFDFFA9A396FFF8FAFDFFA9A296FFF6F7
      FAFFF3F4F6FFF2F3F5FFCECBC4FF9C9486FF00000000ADADABFFFFFFFFFFF8F8
      F7FFFDFDFCFFFDFDFCFFFCFCFAFFFCFCFBFFFEFFFDFFFEFEFDFFFBFBFAFFF7F7
      F6FFFFFFFFFFADADABFF000000000000000000000000000000009B8B2AFFFF25
      00FFB3AB40FFFF2500FFB3AB40FFFF2500FFB3AB40FFB0A835FFB3AB40FFFF25
      00FFB3AB40FFFF2500FF9B8B2AFF0000000000000000D08E24FFFFB76EFFEC9C
      40FFEB9837FFF9E3CBFFFBC794FFE8942FFFE9BE81FFFBE4CCFFEC9838FFEC9C
      40FFFFB76EFFD08E24FF00000000000000009C9486FFD3D2CBFFA49C8EFFA69E
      91FFA7A092FFA7A092FFA7A092FFA7A092FFA7A092FFA7A092FFA7A092FFA59E
      90FFA2998BFFF1F2F4FFD1D0C8FF9C9386FF00000000ADADABFFFFFFFFFFF7F5
      F4FF838383FFB5B3B4FFFAF9F8FF848484FFB6B5B5FFB5B4B4FFB2B0B1FFF5F4
      F2FFFFFFFFFFADADABFF000000000000000000000000000000009B8B2AFFCDCD
      5CFFFF2500FFACA433FFAFA73DFFACA433FFFF2500FFACA433FFAFA73DFFFF25
      00FFFF2500FFCDCD5CFF9B8B2AFF0000000000000000D08E24FFFFBA74FFE79B
      3EFFE8993AFFEFB36DFFFEEDDDFFE79129FFF7EAD6FFEFB46EFFE8993AFFE79B
      3EFFFFBA74FFD08E24FF00000000000000009C9386FFD6D5CDFFF6F7FAFFA199
      8CFFF8FAFDFFA29A8DFFF8FAFDFFA29A8DFFF8FAFDFFA29A8DFFF8FAFDFFA199
      8CFFF5F6F9FFDDD9D7FFD5D4CBFF9C9386FF00000000ADADABFFFFFFFFFFF2F2
      F1FFF8F8F7FFF8F8F7FFF7F7F6FFF7F7F6FFF7F7F6FFF8F8F7FFF5F5F4FFF1F1
      F0FFFFFFFFFFADADABFF000000000000000000000000000000009B8B2AFFCED0
      5EFFACA33AFFA9A030FFACA33AFFA9A030FFACA33AFFA9A030FFACA33AFFA9A0
      30FFACA33AFFCED05EFF9B8B2AFF0000000000000000D08E24FFFFBC78FFE49A
      3AFFE59A3AFFE49430FFFDFBF8FFEEAF63FFFEFBF8FFE4942FFFE59939FFE499
      39FFFFBC77FFD08E24FF00000000000000009C9386FFDADAD1FFB6B0A4FFB8B1
      A6FFB8B1A5FFB8B2A6FFB8B1A5FFB8B2A6FFB8B1A5FFB8B2A6FFB8B1A5FFB8B1
      A6FFB6B0A4FFB6AFA3FFDADAD1FF9C9386FF00000000ADADABFFFFFFFFFFF0EF
      EEFF848484FFB4B2B3FFB2B1B1FFB1B0B0FFF3F2F1FF838383FFAFAEAEFFEFED
      ECFFFFFFFFFFADADABFF000000000000000000000000000000009B8B2AFFD0D2
      61FFA99E37FFA69B2DFFA99E37FFA69B2DFFA99E37FFA69B2DFFA99E37FFA69B
      2DFFA99E37FFD0D261FF9B8B2AFF0000000000000000D08D24FFFFBF7CFFE197
      37FFE29939FFE29533FFEEC38AFFFFFFFFFFECC187FFE0932EFFE09634FFE095
      33FFFFBE7AFFD08D24FF00000000000000009D9487FFDFE1D7FFDDDED4FFDDDE
      D4FFDDDED5FFDDDED5FFDDDED5FFDDDED5FFDDDED5FFDDDED5FFDDDED5FFDDDE
      D5FFDDDED4FFDDDED4FFDFE1D7FF9D9487FF00000000ADADABFFFFFFFFFFEBEB
      EAFFEEEEEDFFEFEFEEFFEEEEEDFFECEDEBFFF6F7F5FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFAEAEABFF000000000000000000000000000000009B8B2AFFD1D4
      63FFA69A33FFA3972AFFA69A33FFA3972AFFA69A33FFA3972AFFA69B34FFA499
      2CFFA69B34FFD1D463FF9B8B2AFF0000000000000000D08D23FFFFC382FFDE95
      32FFE09735FFE09634FFDF932EFFDD9027FFEAA146FFFFC07CFFFFC17DFFFFC0
      7CFFFFC17EFFD08D23FF00000000000000004B4741B09D9587FF9C9386FF9C93
      86FF9C9386FF9C9386FF9C9386FF9C9386FF9C9386FF9C9386FF9C9386FF9C93
      86FF9C9386FF9C9386FF9D9587FF4B4741B000000000ADAEABFFFFFFFFFFE7E6
      E5FFE8E7E6FFE9E8E7FFE9E7E6FFE7E6E5FFFFFFFFFFCCCCCBFFA7A7A5FFA5A5
      A3FFFFFFFFFFAFAFADFF000000000000000000000000000000009B8B2AFFD2D6
      65FFA29631FFA1942AFFA1942FFF9C8F20FF9F9227FFB1A839FFACA335FF9887
      20FF96851FFFD2D661FF9B8B29FF0000000000000000D08D23FFFFC686FFD993
      2DFFDB9532FFDC9633FFDB9531FFD9922BFFFFC483FFE19D3EFFCD8513FFCC84
      12FFFFC381FFD18D23FF0000000000000000000000000000000000000000A098
      8BFF000000330000002400000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000AEAEABFFFFFFFFFFE3E3
      E2FFE4E4E3FFE4E5E4FFE4E4E3FFE3E3E2FFFFFFFFFFA7A7A4FFEBEBEAFFFFFF
      FFFFE9E9E9FF4F4F4EAC000000000000000000000000000000009B8B2AFFD4D8
      67FF9F912EFFA1942FFF9E9129FFA1942FFFA0922EFFD4D968FF968520FFF7F9
      FFFFFFFFFFFFC1BA9DFF423B11A60000000000000000D08D23FFFFC88AFFD68F
      29FFD8922EFFD8932EFFD8922EFFD58F28FFFFC786FFCD8412FFE7F5FFFFFFFF
      FFFFF0AE5AFF604010AC0000000000000000000000000000000000000000504D
      45B5A1998CFF57524BC400000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000AEAEACFFFFFFFFFFE0DF
      DEFFE1DFDEFFE1E0DFFFE1DFDEFFE0DFDEFFFFFFFFFFA5A5A3FFFFFFFFFFE8E8
      E8FF4B4B49A700000000000000000000000000000000000000009B8B2AFFD5D9
      69FF9A8A28FF9C8D2AFF9C8D2AFF9C8D2AFF9A8A28FFD5D868FF94831CFFFFFF
      FFFFBDB794FF3F390EA4000000000000000000000000D18D22FFFFCA8EFFD08B
      1FFFD28D23FFD28D24FFD28D23FFD08A1FFFFFC889FFCC8311FFFFFFFFFFF0AC
      55FF593B0DA70000000000000000000000000000000000000000000000000000
      000000000000A1998CFF00000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000AFAFADFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE9E9E9FF4949
      48A60000000000000000000000000000000000000000000000009B8B2AFFD7DC
      6CFFD7DC6BFFD7DC6CFFD7DC6CFFD7DC6CFFD7DC6BFFD5DA6AFFD6DB67FFC1BA
      9DFF3F390EA400000000000000000000000000000000D18E24FFFFCE93FFFFCC
      92FFFFCD92FFFFCD93FFFFCD92FFFFCC91FFFFCB8EFFFFCB8EFFF0B15FFF583A
      0DA6000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000009D9D9BEFB0B0ADFFAEAE
      ACFFAEAEABFFAEAEABFFAEAEABFFADAEABFFAEAEABFFAFAFADFF949493EA0000
      00000000000000000000000000000000000000000000000000007B6F23E29B8B
      2AFF9B8B29FF9B8B29FF9B8B29FF9B8B29FF9B8B29FF9B8B29FF9B8B29FF786C
      20E00000000000000000000000000000000000000000B97E23EFD18E24FFD18C
      22FFD08C22FFD18C22FFD08C22FFD08C22FFD08C22FFD18C22FFB1771FEA0000
      0000000000000000000000000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002300000000000000000000000001010123030303330303
      0333030303330303033303030333030303330303033303030333030303330303
      0333030303330101012300000000000000000000000000000030000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000003000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000006E155CC0D127ADFFD025
      ACFFD024ACFFD024ACFFD025ACFFD025ACFFD025ACFFD024ACFFD024ACFFD025
      ACFFD127ADFF6E155CC00000000000000000000000000A5100C00C9600FF0B96
      00FF0A9600FF0A9600FF0B9600FF0B9600FF0B9600FF0A9600FF0A9600FF0B96
      00FF0C9600FF0A5100C0000000000000000000000000217BC1F22389D8FF2388
      D8FF2389D8FF2389D8FF2389D8FF2389D8FF2389D8FF2389D8FF2389D8FF2388
      D8FF2389D8FF217BC1F200000000000000000000000000000030000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      00330000003300000033000000300000000000000000D127ADFFFF60F2FFFE55
      F0FFFE4FEFFFFE4EEFFFFE50EFFFFE52F0FFFE50EFFFFE4EEFFFFE4FEFFFFE55
      F0FFFF60F2FFD127ADFF0000000000000000000000000C9600FFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFF0C9600FF0000000000000000000000002389D8FF41C1FFFF3AB4
      FCFF3AB4FDFF3AB4FDFF3AB4FDFF3AB5FDFF3AB5FDFF3AB5FDFF3AB5FDFF3AB4
      FCFF41C1FFFF2389D8FF000000000000000000000000828282F28D8D8DFF8B8B
      8BFF8B8B8BFF8B8B8BFF8B8B8BFF8B8B8CFF8B8B8BFF8B8B8BFF8B8B8CFF8B8B
      8BFF8B8B8BFF8D8D8DFF828282F20000000000000000D025ACFFFF60F1FFC044
      CDFFAB45C6FFA640C1FFB539BEFFE22FC5FFC53696FFBE3D87FFBE3C88FFD84B
      B3FFFF60F1FFD025ACFF0000000000000000000000000B9600FFF7FBFAFF48B1
      99FF78AA9FFF23BE99FF22DFB2FF2CD5AEFF69B7A5FFA5C6CAFFB6D4E1FFDAF7
      FBFFFDFEFFFF0B9600FF0000000000000000000000002087D9FF3DBFFFFF2C9D
      ECFF2D9FEDFF2D9FEDFF2D9FEDFF2D9FEEFF2EA1EFFF2EA2F1FF2DA0EFFF2C9E
      ECFF3DBFFFFF2087D9FF0000000000000000000000008D8D8DFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFF8D8D8DFF0000000000000000D025ACFFFF65F1FF5971
      F4FF7AA9F8FF669EF7FF516DF3FFE12EC4FFE1975DFFF9CF8DFFF9C87EFFE199
      62FFFF65F1FFD025ACFF0000000000000000000000000B9600FFF5FBF9FF11A0
      77FF639287FF63978AFF24B995FF41AD93FF6C988DFF75BEB7FFA7D0DAFFBEDB
      E3FFFCFDFDFF0B9600FF0000000000000000000000001185E3FF2CBBFFFF1086
      E2FF1087E3FF1087E3FF1188E3FF1389E3FF188DE6FF1F467BFF188CE5FF1287
      E2FF2DBBFFFF1185E3FF0000000000000000000000008B8B8BFFFFFFFFFFFDFE
      FEFF7C7C7CFFB1B1B1FFFFFFFFFF7D7D7DFFB1B1B1FFFFFFFFFF7D7D7DFFB1B1
      B1FFFEFEFEFFFFFFFFFF8B8B8BFF0000000000000000D025ACFFFF6AF0FF5478
      FBFFA9C6FDFFB9D2FFFF4974FDFFE02EC3FFE2A15CFFFCE3BDFFFCEACCFFE1A1
      5FFFFF6AF0FFD025ACFF0000000000000000000000000B9600FFF4FCFAFF01B8
      85FF22B691FF639D8EFF8CA29CFF7B9D95FF50BEA3FF87E5DCFFB3D6E2FFD0EE
      F3FFFDFEFEFF0B9600FF000000000000000000000000D0934DFFFFF7C2FFFFEF
      B5FFFFEFB5FFFFEFB5FFFFF0B4FFFFF3B1FFFFFAB2FF14568AFFFFF9B1FFFFF3
      B1FFFFF8C0FFD0934DFF0000000000000000000000008B8B8BFFFFFDFDFFF4F3
      F3FFFFFFFFFF7C7C7CFFF9F8F8FFFFFFFFFF7C7C7CFFF9F8F8FFFFFFFFFF7C7C
      7CFFF7F6F6FFFFFEFEFF8B8B8BFF0000000000000000D024ACFFFF6EF0FFA84F
      D4FF8756D3FF8453D1FFA047CDFFE02DC2FFD14F8FFFC96178FFC96078FFD95D
      9FFFFF6EF0FFD024ACFF0000000000000000000000000A9600FFF4FCFAFF00C1
      8CFF08C696FF29B991FF57C7A7FF53BA9FFF42D7B5FFA1F1EEFFB9D8E7FFDCEE
      E2FFFDFEFDFF0A9600FF000000000000000000000000C19157FFFFF3CBFFFFE5
      B2FFFFE5B2FFFFE5B2FFFFE8AEFF7AC3E5FF27B1FFFF30B5FFFF27B1FFFF7BC3
      E5FFFFF6C7FFC29156FF0000000000000000000000008C8C8CFFFDFBFBFFECEB
      EBFFEDECECFFEFEEEEFFEEEDEDFFEEEDEDFFEFEEEEFFEEEDEDFFEEEDEDFFEFEE
      EEFFEEEDEDFFFDFCFCFF8C8C8CFF0000000000000000D024ACFFFF74F1FFDD7C
      70FFEB9F52FFEC9F52FFDE7A68FFDF2DC1FF6F57D8FF4C70F7FF4C70F7FF725E
      DEFFFF74F1FFD024ACFF0000000000000000000000000A9600FFF4FBF9FF00AF
      7DFF08B98BFF13A39CFF2498B6FF2AC1A0FF58D0BEFFA7DBE7FFB5D4E4FFD4C9
      98FFFDFCFAFF0A9600FF000000000000000000000000BE9158FFFFF3D0FFFFE0
      ACFFFFE0ADFFFFE1ACFFFFE4A7FF16A2FEFF2CA8F7FF32AAF5FF2CA8F6FF17A2
      FDFFFFF8C9FFC09157FF0000000000000000000000008C8C8CFFFCFCFBFFE6E5
      E4FFE6E5E4FFE6E5E4FFE6E5E4FFE6E5E4FFE6E5E4FFE6E5E4FFE6E5E4FFE6E5
      E4FFE6E5E4FFFCFCFBFF8C8C8CFF0000000000000000D024ACFFFF78F1FFE6A4
      5AFFFFE5B8FFFFE2ADFFF0A84CFFDE2CC0FF4F7AFDFFA1C7F8FF95C1F6FF527A
      FBFFFF77F1FFD024ACFF0000000000000000000000000A9600FFF4FBF9FF00B2
      80FF0AB192FF1C6BBBFF2275CCFF36C8ABFF87D2D6FFB7DEF0FFBFC8B6FFE1BC
      64FFFEFCF7FF0A9600FF000000000000000000000000BE9158FFFFF5D4FFFFDD
      A5FFFFDDA7FFFFDDA7FFFFE1A3FF75B5D5FF229DF1FF2A9FEEFF229CF0FF76B5
      D3FFFFF9CFFFBF9157FF0000000000000000000000008C8C8DFFFDFEFDFFE0DF
      DEFFE0DFDEFFE0DFDEFFE0DFDEFFE0DFDEFFE0DFDEFFE0DFDEFFE0DFDEFFE0DF
      DEFFE0DFDEFFFDFEFDFF8C8C8DFF0000000000000000D024ADFFFF7CF1FFE389
      77FFE7B271FFE8B573FFEB8B6BFFDD2CBFFF7466ECFF668CFAFF6A8FFBFF7769
      ECFFFF7AF1FFD024ADFF0000000000000000000000000B9600FFF4FCF8FF00C3
      8CFF0BBC9BFF1B78BAFF30AAD0FF65D6CEFFABDBECFFD6E7D5FFD3BB77FFF4C7
      60FFFEFCF7FF0B9600FF000000000000000000000000BE9158FFFFF7D6FFFFDA
      9CFFFFDA9EFFFFDA9FFFFFDC9DFFFFE098FF0585E9FF0F88E5FF0685E7FFFFE0
      93FFFFF8D4FFBF9158FF0000000000000000000000008D9092FFFFFFFFFFF3F4
      F6FFF2F4F6FFF2F4F6FFF2F4F6FFF2F4F6FFF2F4F6FFF2F4F6FFF2F4F6FFF2F4
      F6FFF3F4F6FFFFFFFFFF8D9092FF0000000000000000D023ACFFFF82F0FFDE32
      C1FFE035C3FFE034C4FFDF2EC2FFDD27BEFFEA46D1FFFF7CF0FFFF7DEFFFFF7C
      F0FFFF7EF0FFD023ACFF0000000000000000000000000B9700FFF4FCF3FF00B7
      84FF0BAE99FF17B296FF4BD1C4FF91CDE1FF169200FF278502FF278503FF2785
      02FF278403FF0B9700FF000000000000000000000000BF9157FFFFF9D7FFFFD8
      8FFFFFD990FFFFD993FFFFD897FFFFD995FFFFE5A9FFFFFBCFFFFFFBD1FFFFF8
      D3FFFFF9D8FFBE9158FF000000000000000000000000917965FF88674AFF8563
      45FF846245FF846245FF846245FF846245FF846245FF846245FF846245FF8462
      45FF856345FF88674AFF917965FF0000000000000000D023ACFFFF86F0FFD92D
      B9FFDB32BCFFDC33BDFFDB31BBFFD92BB8FFFF83EFFFE13EC4FFCD13A6FFCC12
      A5FFFF81F0FFD123ADFF0000000000000000000000000B9700FFF4FBEEFF029F
      82FF156BB2FF26B89BFF76C6D2FFAAC0C3FF288306FF139200FF059C00FF059C
      00FF288405FF0A9700FF000000000000000000000000C09157FFFFFAD5FF1BB7
      FFFF22B8FFFF79C4DDFFFFD58CFFFFD38EFFFFF6D9FFD8B380FFBB884AFFB886
      48FFFFFBDDFFBF9259FF0000000000000000000000008F6F54FFFFFFF9FFF9F4
      EDFFF9F3ECFFF9F3ECFFF9F3ECFFF9F3ECFFF9F3ECFFF9F3ECFFF9F3ECFFF9F3
      ECFFF9F4EDFFFFFFF9FF8F6F54FF0000000000000000D023ACFFFF8AF0FFD629
      B6FFD82EB8FFD82EB7FFD82EB8FFD528B4FFFF86EFFFCD12A7FFE7FFE8FFFFFF
      FFFFF05AD8FF60104EAC0000000000000000000000000B9700FFF4FAE9FF039B
      A4FF2040DFFF3DC5B1FFADDBE7FFD2C28AFF288208FF059C00FF594A62FF5252
      52FF1B8D00FF087900E4000000000000000000000000C19156FFFFFBD7FF26C1
      FFFF32C3FFFF26C3FFFFFFD082FFFFCE86FFFFF8DEFFB9874AFFE9F0FAFFFFFF
      FFFFEED4ACFF584329AC0000000000000000000000008D6E54FFFCF5EEFFE9DC
      CBFFE9DBCAFFE9DBCBFFE9DBCBFFE9DBCBFFE9DBCBFFE9DBCBFFE9DBCBFFE9DB
      CAFFE9DCCBFFFCF5EEFF8D6E54FF0000000000000000D122ACFFFF8EF0FFD01F
      ACFFD223AEFFD224AFFFD223AEFFD01FADFFFF89EFFFCC11A6FFFFFFFFFFF055
      D7FF590D49A7000000000000000000000000000000000A9800FFF5F7E6FF1CA2
      ACFF2684CFFF5AC7C4FFC4D8C4FFE9C269FF29810AFF059C00FF525252FF198F
      00FF5DB84FFF00000000000000000000000000000000C09157FFFFFCDCFF81C9
      D0FF2CCBFFFF24CBFFFFFFCA77FFFFC97BFFFFF8DFFFB78547FFFFFFFFFFEDD3
      AAFF513D25A7000000000000000000000000000000008F7157FFFFFFFBFFF6EE
      E1FFF5EDE1FFF5EDE1FFF5EDE1FFF5EDE1FFF5EDE1FFF5EDE1FFF5EDE1FFF5ED
      E1FFF6EEE1FFFFFFFBFF8F7157FF0000000000000000D124ADFFFF93EFFFFF92
      F0FFFF92EFFFFF93F0FFFF92EFFFFF91F0FFFF8EEFFFFF8EEFFFF05FD8FF580D
      48A600000000000000000000000000000000000000000B9700FFFFF9EAFFFFF9
      E2FFFFF9E1FFFFF7E1FFFFF5E3FFFFF5E7FF2A7E0DFF2A7E0DFF1C8B00FF5EB8
      50FF0000000000000000000000000000000000000000C0935AFFFFFFE7FFFFFD
      DFFFFFFDDCFFFFFDDEFFFFFDE3FFFFFCE4FFFFFDE4FFFFFFE6FFEED5AFFF503C
      24A6000000000000000000000000000000000000000045382CB08F7157FF8D6E
      54FF8D6E54FF8D6E54FF8D6E54FF8D6E54FF8D6E54FF8D6E54FF8D6E54FF8D6E
      54FF8D6E54FF8F7157FF574637C50000000000000000B9239BEFD124ADFFD122
      ADFFD022ACFFD122ADFFD022ACFFD022ACFFD022ACFFD122ADFFB11F93EA0000
      000000000000000000000000000000000000000000000C8400EF0B9700FF0A97
      00FF0A9700FF0A9700FF0A9700FF0A9700FF0A9700FF0A9700FF0A9500FD0000
      00000000000000000000000000000000000000000000AA8454EFC09359FFC091
      57FFC09056FFC09056FFBF9057FFBE9057FFBE9057FFBF9158FFA27D4CEA0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002300000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002300000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002300000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      00330000003300000023000000000000000000000000050096EF0500C0FF0500
      BFFF0500BFFF0500BFFF0500BFFF0500BFFF0500BFFF0500BFFF0500BFFF0500
      BFFF0500C0FF050096EF000000000000000000000000653D18C0C1742EFFC173
      2DFFC0722CFFC0722BFFC0722CFFC1732EFFC1742EFFC1742FFFC1742FFFC174
      2EFFC1742EFF653D18C00000000000000000000000005C4E1EC0B1963AFFB196
      39FFB19639FFB19639FFB19638FFB19538FFB19638FFB19639FFB19639FFB196
      39FFB1963AFF5C4E1EC00000000000000000000000001E3D64C03871BCFF3770
      BBFF366FBDFF366FBDFF3571BCFF366FBDFF366FBDFF3770BEFF3770BEFF3770
      BBFF3871BCFF1E3D64C00000000000000000000000000500C0FF0600D3FF0600
      CEFF0600CBFF0600CAFF0600CCFF0600CDFF0600CCFF0600CAFF0600CBFF0600
      CEFF0600D3FF0500C0FF000000000000000000000000C1742EFFD0A220FFCC99
      17FFCA950EFFC9920AFFCA950EFFCC9917FFCC9A1AFFCC9A1AFFCD9B1BFFCD9B
      1CFFD0A321FFC1742EFF000000000000000000000000B19639FFCCC363FFC8BB
      5CFFC8BB5CFFC8BB5BFFC6B957FFC5B854FFC6BA57FFC8BB5BFFC8BB5CFFC8BB
      5CFFCCC363FFB19639FF0000000000000000000000003871BFFF69AAE0FF5EA2
      DFFFFFFFFFFFFFFFFFFFFFFFFFFF27496AFF59A0DDFFFFFFFFFFFFFFFFFFFFFF
      FFFF69AAE0FF3871BFFF0000000000000000000000000500BFFF0600D3FF0600
      C9FF0600C6FFFFFFFFFF0600C5FF0500C3FF0500C0FFFFFFFFFF0500C0FF0600
      C9FF0600D3FF0500BFFF000000000000000000000000C0732DFFD2A428FFC78E
      0FFFFBF9F1FFFFFFFFFFFBF8F0FFC68C0BFFC78D0FFFC68C0CFFC88E11FFC992
      19FFD2A42AFFC0732DFF000000000000000000000000B19539FFCDC265FFC4B6
      57FFC3B555FFC1B34FFFBDAE44FFFFFFFFFFBFB048FFC1B24EFFC2B453FFC4B6
      56FFCDC265FFB19539FF0000000000000000000000003770BBFF69A7DDFF5492
      D1FFFFFFFFFF000000FFFFFFFFFF5492D1FF294767FFFFFFFFFF000000FFFFFF
      FFFF69A7DDFF3770BBFF0000000000000000000000000500BFFF0600D7FF0600
      C6FFFFFFFFFF0600C5FFFFFFFFFF0500C3FFFFFFFFFF000000FFFFFFFFFF0600
      C6FF0600D7FF0500BFFF000000000000000000000000C0732DFFD5A731FFC589
      0CFFFFFFFFFFFFFFFFFFFFFFFFFFC18100FFFBF7EFFFFFFFFFFFFBF8F2FFC68B
      10FFD5A732FFC0732DFF000000000000000000000000B09538FFCFC468FFC1B0
      4EFFBEAC45FFBAA73AFFFFFFFFFFFFFFFFFFBAA73AFFFFFFFFFFBEAC45FFC1B0
      4EFFCFC468FFB09538FF0000000000000000000000003770BEFF6FAFE2FF5094
      D4FFFFFFFFFFFFFFFFFFFFFFFFFF274868FF5094D4FFFFFFFFFFFFFFFFFFFFFF
      FFFF6FAFE2FF3770BEFF0000000000000000000000000500BFFF0600DBFF0600
      C8FF0600C6FFFFFFFFFF000000FFFFFFFFFF000000FFFFFFFFFF0500C0FF0600
      C8FF0600DBFF0500BFFF000000000000000000000000C0732CFFD8AA3BFFC487
      12FFFBF7F0FFFFFFFFFFFFFFFFFFBF7A00FFFFFFFFFFFFFFFFFFFFFFFFFFC384
      0CFFD7A939FFC0732CFF000000000000000000000000B09538FFD1C76BFFBBA9
      44FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB7A336FFEDE7CCFFEEEAD0FFBCAA
      47FFD1C86BFFB09538FF0000000000000000000000003770BEFF71ACDFFF4F96
      D3FF448ED1FF1D4265FF3D8BD1FF428AD0FF438DD0FF214467FF4993D3FF2649
      68FF71ACDFFF3770BEFF0000000000000000000000000500BFFF0700DDFF0600
      C6FFFFFFFFFF000000FF000000FF000000FF000000FF000000FFFFFFFFFF0600
      C6FF0700DDFF0500BFFF000000000000000000000000C0722BFFDCAE44FFC588
      1CFFC38412FFBF7A01FFFFFFFFFFBF7900FFFAF5EBFFFFFFFFFFFFFFFFFFC180
      0CFFDBAD42FFC0722BFF000000000000000000000000B09537FFD4C86FFFB7A4
      3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB5A035FFB6A135FFFFFFFFFFB9A5
      40FFD4C970FFB09537FF0000000000000000000000003770BEFF74ABE1FF4788
      CBFF1F4164FF3F83C9FF1C3F64FF3B82CBFF387EC8FF347AC8FF224264FF4788
      CBFF74ABE1FF3770BEFF0000000000000000000000000500BFFF0F00DEFF0600
      C7FFFFFFFFFF000000FFFFFFFFFF000000FFFFFFFFFF000000FFFFFFFFFF0600
      C7FF0F00DEFF0500BFFF000000000000000000000000C0722BFFDFB34EFFC587
      21FFC5871FFFC17D0FFFFFFFFFFFBE7501FFBE7704FFBC7300FFFFFFFFFFC07B
      0DFFDDB14BFFC0722BFF000000000000000000000000B09537FFD7CB73FFB8A3
      3CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB49D2FFFEDE7CBFFECE7CDFFB9A4
      3FFFD7CB74FFB09537FF0000000000000000000000003770BEFF76ADE0FF4488
      CEFFFFFFFFFFFFFFFFFFFFFFFFFF3B82CBFF1B3E62FFFFFFFFFFFFFFFFFFFFFF
      FFFF76ADE0FF3770BEFF0000000000000000000000000500BFFF1700E1FF0600
      C5FF0600C6FFFFFFFFFF000000FF000000FF000000FFFFFFFFFF0500C0FF0600
      C6FF1400E0FF0500BFFF000000000000000000000000BF722AFFE2B658FFC584
      22FFC68422FFC27B11FFFFFFFFFFF4E6D3FFE2C18EFFCE9741FFFFFFFFFFC077
      0DFFE1B455FFBF722AFF000000000000000000000000B09537FFDACF79FFB8A3
      42FFB6A03BFFB29B2FFFFFFFFFFFFFFFFFFFB29A2EFFFFFFFFFFB6A03AFFB8A3
      42FFDACF79FFB09537FF0000000000000000000000003672BDFF79ADE0FF4286
      CCFFFFFFFFFF000000FFFFFFFFFF183B61FF3278C6FFFFFFFFFF000000FFFFFF
      FFFF79ADE0FF3672BDFF0000000000000000000000000500BDFF1C00E4FF0600
      C4FF0600C6FF0600C5FFFFFFFFFF000000FFFFFFFFFF0500C0FF0500C0FF0600
      C4FF1900E2FF0500BDFF000000000000000000000000BF7229FFE5BA60FFC482
      24FFC58325FFC17A17FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBD73
      0DFFE3B85CFFBF7229FF000000000000000000000000B09437FFDCD27DFFB9A2
      42FFBAA344FFB8A13EFFB39B32FFFFFFFFFFB39B34FFB59D39FFB69F3DFFB69F
      3FFFDCD17CFFB09437FF000000000000000000000000366FBAFF80B0E3FF3B77
      C2FFFFFFFFFFFFFFFFFFFFFFFFFF3272C2FF18385FFFFFFFFFFFFFFFFFFFFFFF
      FFFF7BAFE5FF366FBDFF0000000000000000000000000500BDFF2300E7FF0500
      C3FF0600C6FF0600C5FF0500C1FFFFFFFFFF0600CDFF1B00E4FF1C00E5FF1B00
      E4FF1E00E5FF0500BDFF000000000000000000000000BF7229FFE8BE69FFC27D
      24FFC48027FFC27C20FFD29E58FFE2C095FFFAF1E1FFFFFFFFFFFFFFFFFFE4B3
      57FFE7BB63FFBF7128FF000000000000000000000000B09437FFDFD482FFB69F
      41FFB9A144FFB8A143FFB79F3FFFB49B39FFC2B053FFDDD27DFFDDD27DFFDDD1
      7DFFDED37EFFB09436FF000000000000000000000000366FBDFF83B0E0FF3C78
      C3FF3A76C4FF3874C2FF3473C1FF3874C2FF508BCEFF76AAE0FF75A9DCFF7CAD
      E0FF81AEDEFF366FBDFF0000000000000000000000000500BDFF2800EAFF0500
      C2FF0600C5FF0600C6FF0600C5FF0500C3FF2300E8FF0600CCFF0500B1FF0500
      B0FF2000E7FF0500BDFF000000000000000000000000BF7128FFEBC171FFC179
      25FFC37D28FFC37C27FFC17922FFBE7319FFE7B760FFC9812BFFB8610DFFB963
      14FFEABE6BFFBF7228FF000000000000000000000000B09436FFE2D786FFB49C
      3DFFB69F41FFB7A042FFB69F40FFB49C3CFFE1D684FFBEA84CFFAA8C28FFA98B
      27FFE0D582FFB09436FF000000000000000000000000366FBDFF89B3E3FF3B7B
      C6FF3D79C4FF417EC5FF4081C7FF3E7EC5FF87B1E1FF4980C6FF2464B8FF2464
      B8FF83B0E0FF366FBDFF0000000000000000000000000500BDFF2C00EAFF0500
      BEFF0500C2FF0500C3FF0500C2FF0500BEFF2600EBFF0500B0FFFFD4F3FFFFFF
      FFFF0600D9FF000794E4000000000000000000000000BF7127FFEFC57AFFC075
      24FFC17928FFC27929FFC17828FFBF7422FFEDC175FFBA6615FFEBF8FFFFFFFF
      FFFFDBA252FF583412AC000000000000000000000000AF9436FFE4DA8BFFB298
      3AFFB49B3EFFB59C3FFFB59B3EFFB2983AFFE3D888FFAA8C28FFEEF3FFFFFFFF
      FFFFCEBD62FF4F4319AC000000000000000000000000366FBDFF8CB6E2FF3C79
      C0FF3F78BFFF4079C0FF3F78BFFF3C79C0FF87B0E3FF2969B9FFFFF6F1FFFFFF
      FFFF6498D2FF193356AC0000000000000000000000000500BDFF3300EDFF0500
      B9FF0500BDFF0500BDFF0500BDFF0500B9FF2C00ECFF0500ADFFFFFFFFFF0600
      D6FF000A8EE100000000000000000000000000000000BF7127FFF1C884FFBC6E
      22FFBD7125FFBE7226FFBD7125FFBC6D22FFEFC480FFB96515FFFFFFFFFFDAA0
      50FF502F0FA700000000000000000000000000000000AF9436FFE5DC8EFFAE91
      32FFAF9436FFB09537FFAF9436FFAD9132FFE3D98AFFA88B26FFFFFFFFFFCDBB
      5EFF4A3E15A7000000000000000000000000000000003571BCFF8EB5E1FF306A
      BBFF366FBDFF3672BDFF366FBDFF336FBDFF8BB1E1FF2767B7FFFFFFFFFF5E95
      D2FF162F50A7000000000000000000000000000000000500BDFF3A00F1FF3A00
      EFFF3900F0FF3B00F0FF3900F0FF3800EFFF3400F0FF3400F0FF0600DAFF000A
      8CE00000000000000000000000000000000000000000BF7228FFF5CD8EFFF4CC
      8DFFF5CC8DFFF5CC8EFFF5CC8DFFF4CB8CFFF3C98AFFF3C988FFDEA55EFF502F
      0EA60000000000000000000000000000000000000000B09537FFE8DF93FFE7DE
      92FFE8DF92FFE8DF93FFE8DF92FFE7DE91FFE6DC8FFFE6DC8EFFD0BF67FF493E
      15A600000000000000000000000000000000000000003672BDFF91B7E7FF90B6
      E6FF91B8E4FF91B4E4FF91B8E4FF90B7E3FF8EB4E4FF8DB3E3FF6797D1FF162F
      4FA600000000000000000000000000000000000000000500BCFE0500BDFF0500
      BCFF0500BCFF0500BCFF0500BCFF0500BCFF0500BCFF0500BCFF0500B9FD0000
      00000000000000000000000000000000000000000000A96726EFBF7227FFBE71
      26FFBE7126FFBE7126FFBE7126FFBE7126FFBE7025FFBF7126FFA06021EA0000
      000000000000000000000000000000000000000000009C8533EFB09537FFAF94
      36FFAF9436FFAF9436FFAF9436FFAF9436FFAF9335FFAF9436FF947E2EEA0000
      000000000000000000000000000000000000000000003166A8EF3672BDFF3571
      BCFF3571BCFF3571BCFF3571BCFF3571BCFF356EBCFF3571BCFF2E5F9FEA0000
      0000000000000000000000000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002300000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002300000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002300000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      00330000003300000023000000000000000000000000483F33C08A7760FF8976
      5FFF88755DFF88755DFF88745DFF88755DFF88755DFF89765EFF89765EFF8976
      5FFF8A7760FF483F33C00000000000000000000000006E4A15C0D18F27FFD08E
      25FFD08E24FFD08E24FFD08E25FFD08E25FFD08E25FFD08E24FFD08E24FFD08E
      25FFD18F27FF6E4A15C00000000000000000000000006E4A15C0D18F27FFD08E
      25FFD08E24FFD08E24FFD08E25FFD08E25FFD08E25FFD08E24FFD08E24FFD08E
      25FFD18F27FF6E4A15C00000000000000000000000006E4A15C0D18F27FFD08E
      25FFD08E24FFD08E24FFD08E25FFD08E25FFD08E25FFD08E24FFD08E24FFD08E
      25FFD18F27FF6E4A15C00000000000000000000000008A775FFFAE9A89FFA893
      80FFA48F7AFFA28D77FFA28C77FFA28D77FFA48E7AFFA6917CFFA6917DFFA994
      81FFAE9A89FF8A775FFF000000000000000000000000D18F27FFFFAD60FFFEA7
      55FFFEA44FFFFEA44EFFFEA550FFFEA652FFFEA550FFFEA44EFFFEA44FFFFEA7
      55FFFFAD60FFD18F27FF000000000000000000000000D18F27FFFFAD60FFFEA7
      55FFFEA44FFFFEA44EFFFEA550FFFEA652FFFEA550FFFEA44EFFFEA44FFFFEA7
      55FFFFAD60FFD18F27FF000000000000000000000000D18F27FFFFAD60FFFEA7
      55FFFEA44FFFFEA44EFFFEA550FFFEA652FFFEA550FFFEA44EFFFEA44FFFFEA7
      55FFFFAD60FFD18F27FF00000000000000000000000089765FFFAD9A89FF9F8C
      77FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9B8670FFFFFFFFFFA08C
      78FFAD9A89FF89765FFF000000000000000000000000D08E25FFFFAE60FFF7A0
      46FFF7A046FFF19C3FFFEA9837FFE2942FFFDD9129FFDD9129FFDD9027FFF7A0
      46FFFFAE60FFD08E25FF000000000000000000000000D08E25FFFFAE60FFF7A0
      46FFF7A046FFF19C3FFFEA9837FFE2942FFFDD9129FFDD9129FFDD9027FFF7A0
      46FFFFAE60FFD08E25FF000000000000000000000000D08E25FFFFAE60FFFFFF
      FFFFFFFFFFFFE09634FFFFFFFFFFFFFFFFFFDE922DFFFFFFFFFFDD9027FFFFFF
      FFFFFFAE60FFD08E25FF00000000000000000000000089765EFFB09C8CFF9D88
      73FF967E69FF927A64FF947B65FF957E69FF957D68FF968069FF98816CFF9D88
      73FFB09C8CFF89765EFF000000000000000000000000D08E25FFFFB165FFF29D
      42FFF29D42FFED9A3CFFFFFFFFFFFFFFFFFFFFFFFFFFDD9129FFDD9027FFF29D
      42FFFFB165FFD08E25FF000000000000000000000000D08E25FFFFB165FFF29D
      42FFF29D42FFFFFFFFFFE79735FFE1932EFFFFFFFFFFDD9129FFDD9027FFF29D
      42FFFFB165FFD08E25FF000000000000000000000000D08E25FFFFB165FFFFFF
      FFFFFFFFFFFFE09634FFE09634FFFFFFFFFFDE922DFFFFFFFFFFDD9027FFFFFF
      FFFFFFB165FFD08E25FF00000000000000000000000089765EFFB19F8FFF9A84
      70FFFFFFFFFFFFFFFFFFFFFFFFFF947D67FFFFFFFFFFFFFFFFFFFFFFFFFF9A84
      70FFB19F8FFF89765EFF000000000000000000000000D08E25FFFFB56AFFEF9D
      41FFEF9D41FFFFFFFFFFE69735FFE0932EFFDD9129FFDD9129FFDD9027FFEF9D
      41FFFFB56AFFD08E25FF000000000000000000000000D08E25FFFFB56AFFEF9D
      41FFEF9D41FFFFFFFFFFE69735FFE0932EFFFFFFFFFFDD9129FFDD9027FFEF9D
      41FFFFB56AFFD08E25FF000000000000000000000000D08E25FFFFB56AFFFFFF
      FFFFFFFFFFFFE09634FFFFFFFFFFFFFFFFFFDE922DFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFB56AFFD08E25FF00000000000000000000000089765EFFB3A291FF9783
      6DFF927C66FF907A64FF907962FF907962FF8D765FFF8D765EFF907963FF9783
      6DFFB3A291FF89765EFF000000000000000000000000D08E24FFFFB76EFFEC9C
      40FFEC9C40FFFFFFFFFFE49634FFE0932DFFDD9129FFDD9129FFDD9027FFEC9C
      40FFFFB76EFFD08E24FF000000000000000000000000D08E24FFFFB76EFFEC9C
      40FFEC9C40FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDD9129FFDD9027FFEC9C
      40FFFFB76EFFD08E24FF000000000000000000000000D08E24FFFFB76EFFEC9C
      40FFFFFFFFFFE09634FFFFFFFFFFDF9431FFDE922DFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFB76EFFD08E24FF00000000000000000000000089765EFFB5A494FF9580
      69FFFFFFFFFF8F7961FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF947E
      68FFB5A494FF89765EFF000000000000000000000000D08E24FFFFBA74FFE79B
      3EFFE79B3EFFFFFFFFFFE29633FFDF932DFFDD9129FFDD9129FFDD9027FFE79B
      3EFFFFBA74FFD08E24FF000000000000000000000000D08E24FFFFBA74FFE79B
      3EFFE79B3EFFFFFFFFFFE29633FFDF932DFFFFFFFFFFDD9129FFDD9027FFE79B
      3EFFFFBA74FFD08E24FF000000000000000000000000D08E24FFFFBA74FFFFFF
      FFFFFFFFFFFFE09634FFFFFFFFFFFFFFFFFFDE922DFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFBA74FFD08E24FF00000000000000000000000089755EFFB7A797FF937D
      67FF8E7860FF8C755DFF89725AFF89725AFF8B745CFF89725AFF8B755DFF927C
      66FFB7A797FF89755EFF000000000000000000000000D08E24FFFFBC78FFE49A
      3AFFE49A3AFFE29836FFFFFFFFFFFFFFFFFFFFFFFFFFDD9129FFDD9027FFE499
      39FFFFBC77FFD08E24FF000000000000000000000000D08E24FFFFBC78FFE49A
      3AFFE49A3AFFFFFFFFFFE09531FFDE922CFFFFFFFFFFDD9129FFDD9027FFE499
      39FFFFBC77FFD08E24FF000000000000000000000000D08E24FFFFBC78FFE49A
      3AFFE09735FFE09634FFE09634FFDF9431FFDE922DFFDD9129FFDD9027FFE499
      39FFFFBC77FFD08E24FF00000000000000000000000088755EFFB9AA9AFF8E7A
      63FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF89745BFFFFFFFFFFFFFFFFFF8C78
      60FFB9A998FF88755DFF000000000000000000000000D08D24FFFFBF7CFFE197
      37FFE19737FFE09534FFDF9430FFDD922CFFDD9129FFDD9129FFDD9027FFE095
      33FFFFBE7AFFD08D24FF000000000000000000000000D08D24FFFFBF7CFFE197
      37FFE19737FFE09534FFDF9430FFDD922CFFDD9129FFDD9129FFDD9027FFE095
      33FFFFBE7AFFD08D24FF000000000000000000000000D08D24FFFFBF7CFFE197
      37FFE09735FFE09634FFE09634FFDF9431FFDE922DFFDD9129FFDD9027FFE095
      33FFFFBE7AFFD08D24FF00000000000000000000000088755DFFBBAD9EFF8F7B
      64FF8D7961FF8B775FFF8B765EFF8B775FFF9B8973FFB4A493FFB3A393FFB6A7
      97FFB9AB9CFF88755DFF000000000000000000000000D08D23FFFFC382FFDE95
      32FFE09735FFE09634FFDF932EFFDD9027FFEAA146FFFFC07CFFFFC17DFFFFC0
      7CFFFFC17EFFD08D23FF000000000000000000000000D08D23FFFFC382FFDE95
      32FFE09735FFE09634FFDF932EFFDD9027FFEAA146FFFFC07CFFFFC17DFFFFC0
      7CFFFFC17EFFD08D23FF000000000000000000000000D08D23FFFFC382FFDE95
      32FFE09735FFE09634FFDF932EFFDD9027FFEAA146FFFFC07CFFFFC17DFFFFC0
      7CFFFFC17EFFD08D23FF00000000000000000000000088755DFFBDB0A1FF8F7A
      63FF907C65FF907C66FF907B65FF8E7963FFBBAE9FFF96856EFF7E6A50FF7E6A
      50FFBBAD9EFF88755DFF000000000000000000000000D08D23FFFFC686FFD993
      2DFFDB9532FFDC9633FFDB9531FFD9922BFFFFC483FFE19D3EFFCD8513FFCC84
      12FFFFC381FFD18D23FF000000000000000000000000D08D23FFFFC686FFD993
      2DFFDB9532FFDC9633FFDB9531FFD9922BFFFFC483FFE19D3EFFCD8513FFCC84
      12FFFFC381FFD18D23FF000000000000000000000000D08D23FFFFC686FFD993
      2DFFDB9532FFDC9633FFDB9531FFD9922BFFFFC483FFE19D3EFFCD8513FFCC84
      12FFFFC381FFD18D23FF00000000000000000000000088755DFFBFB2A4FF8B77
      61FF8D7A64FF8E7B65FF8D7A64FF8B7761FFBEB1A1FF806B52FFF7FAFEFFFFFF
      FFFFA69684FF3D352BAC000000000000000000000000D08D23FFFFC88AFFD68F
      29FFD8922EFFD8932EFFD8922EFFD58F28FFFFC786FFCD8412FFE7F5FFFFFFFF
      FFFFF0AE5AFF604010AC000000000000000000000000D08D23FFFFC88AFFD68F
      29FFD8922EFFD8932EFFD8922EFFD58F28FFFFC786FFCD8412FFE7F5FFFFFFFF
      FFFFF0AE5AFF604010AC000000000000000000000000D08D23FFFFC88AFFD68F
      29FFD8922EFFD8932EFFD8922EFFD58F28FFFFC786FFCD8412FFE7F5FFFFFFFF
      FFFFF0AE5AFF604010AC00000000000000000000000088745DFFC0B4A6FF8673
      5AFF88755DFF89755EFF88755DFF86725AFFBEB2A3FF7D6950FFFFFFFFFFA493
      80FF393027A700000000000000000000000000000000D18D22FFFFCA8EFFD08B
      1FFFD28D23FFD28D24FFD28D23FFD08A1FFFFFC889FFCC8311FFFFFFFFFFF0AC
      55FF593B0DA700000000000000000000000000000000D18D22FFFFCA8EFFD08B
      1FFFD28D23FFD28D24FFD28D23FFD08A1FFFFFC889FFCC8311FFFFFFFFFFF0AC
      55FF593B0DA700000000000000000000000000000000D18D22FFFFCA8EFFD08B
      1FFFD28D23FFD28D24FFD28D23FFD08A1FFFFFC889FFCC8311FFFFFFFFFFF0AC
      55FF593B0DA70000000000000000000000000000000089755EFFC4B8A9FFC3B7
      A8FFC3B7A9FFC3B8A9FFC3B7A9FFC2B6A8FFC1B5A6FFC0B4A5FFA89987FF3830
      26A60000000000000000000000000000000000000000D18E24FFFFCE93FFFFCC
      92FFFFCD92FFFFCD93FFFFCD92FFFFCC91FFFFCB8EFFFFCB8EFFF0B15FFF583A
      0DA60000000000000000000000000000000000000000D18E24FFFFCE93FFFFCC
      92FFFFCD92FFFFCD93FFFFCD92FFFFCC91FFFFCB8EFFFFCB8EFFF0B15FFF583A
      0DA60000000000000000000000000000000000000000D18E24FFFFCE93FFFFCC
      92FFFFCD92FFFFCD93FFFFCD92FFFFCC91FFFFCB8EFFFFCB8EFFF0B15FFF583A
      0DA600000000000000000000000000000000000000007A6854EF89755EFF8874
      5DFF88745DFF88745DFF88745DFF88745DFF87745CFF88745DFF73634FEA0000
      00000000000000000000000000000000000000000000B97E23EFD18E24FFD18C
      22FFD08C22FFD18C22FFD08C22FFD08C22FFD08C22FFD18C22FFB1771FEA0000
      00000000000000000000000000000000000000000000B97E23EFD18E24FFD18C
      22FFD08C22FFD18C22FFD08C22FFD08C22FFD08C22FFD18C22FFB1771FEA0000
      00000000000000000000000000000000000000000000B97E23EFD18E24FFD18C
      22FFD08C22FFD18C22FFD08C22FFD08C22FFD08C22FFD18C22FFB1771FEA0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      003300000033000000230000000000000000000000570000005C0000005C0000
      005C0000005C0000005C0000005C0000005C0000005C0000005C0000005C0000
      005C0000005C000000550000000000000000000000570000005C0000005C0000
      005C0000005C0000005C0000005C0000005C0000005C0000005C0000005C0000
      005C0000005C000000550000000000000000000000570000005C0000005C0000
      005C0000005C0000005C0000005C0000005C0000005C0000005C0000005C0000
      005C0000005C00000055000000000000000000000000483117C08A5D2AFF895D
      2AFF895C29FF895C29FF895C28FF895B28FF895C28FF895C29FF895C29FF895D
      2AFF8A5D2AFF483117C000000000000000004496CFFE4298D2FF3F94D0FF3D92
      CFFF3D92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92
      CEFF3E93CFFF4092CCFE0000001B000000004496CFFE4298D2FF3F94D0FF3D92
      CFFF3D92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92
      CEFF3E93CFFF4092CCFE0000001B000000004496CFFE4298D2FF3F94D0FF3D92
      CFFF3D92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92
      CEFF3E93CFFF4092CCFE0000001B00000000000000008A5D2AFFAE8D5AFFAA86
      52FFA98550FFA7824CFFA6814AFFA57E48FFA6814AFFA7824CFFA98550FFAA86
      52FFAE8D5AFF8A5D2AFF00000000000000004399D2FF3E94D0FFABFBFFFF9BF3
      FFFF92F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1
      FFFFA6F8FFFF64B8E3FF1229399B000000004399D2FF3E94D0FFABFBFFFF9BF3
      FFFF92F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1
      FFFFA6F8FFFF64B8E3FF1229399B000000004399D2FF3E94D0FFABFBFFFF9BF3
      FFFF92F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1
      FFFFA6F8FFFF64B8E3FF1229399B0000000000000000895C29FFB18E5BFFA27D
      49FF9E7740FFD8C8B1FF966C31FFFFFFFFFF966C31FFD8C8B1FF9E7740FFA27D
      49FFB18E5BFF895C29FF00000000000000004298D2FF4EA6D9FF8EDAF5FFA2EE
      FFFF82E5FEFF84E5FEFF84E5FEFF85E6FEFF85E6FEFF85E6FEFF85E6FEFF84E6
      FEFF96EBFFFF8CD8F5FF30709FEB000000004298D2FF4EA6D9FF8EDAF5FFA2EE
      FFFF82E5FEFF84E5FEFF84E5FEFF85E6FEFF85E6FEFF85E6FEFF85E6FEFF84E6
      FEFF96EBFFFF8CD8F5FF30709FEB000000004298D2FF4EA6D9FF8EDAF5FFA2EE
      FFFF82E5FEFF84E5FEFF84E5FEFF85E6FEFF85E6FEFF85E6FEFF85E6FEFF84E6
      FEFF96EBFFFF8CD8F5FF30709FEB0000000000000000895C29FFB3925DFF9E76
      41FFD7C6B0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD7C6B0FF9E76
      41FFB3925DFF895C29FF00000000000000004196D1FF6ABEE8FF6CBDE6FFBBF2
      FFFF74DEFDFF76DEFCFF77DEFCFF7ADFFCFF7CDFFCFF7CDFFCFF7CDFFCFF7BDF
      FCFF80E0FDFFADF0FFFF4C9DD3FF0000001B4196D1FF6ABEE8FF6CBDE6FFBBF2
      FFFF74DEFDFF76DEFCFF77DEFCFF7ADFFCFF7CDFFCFF7CDFFCFF7CDFFCFF7BDF
      FCFF80E0FDFFADF0FFFF4C9DD3FF0000001B4196D1FF6ABEE8FF6CBDE6FFBBF2
      FFFF74DEFDFF76DEFCFF77DEFCFF7ADFFCFF7CDFFCFF7CDFFCFF7CDFFCFF7BDF
      FCFF80E0FDFFADF0FFFF4C9DD3FF0000001B00000000885B28FFB69561FF9A71
      3CFF916429FFFFFFFFFFCFBBA0FF916328FFCFBBA0FFFFFFFFFF916429FF9A71
      3CFFB69561FF885B28FF00000000000000003F95D0FF8AD7F5FF43A1D8FFDDFD
      FFFFDAFAFFFFDBFAFFFFDEFAFFFF73DCFCFF75DBFAFF74DAFAFF73DAFAFF73DA
      FAFF71D9FAFFA1E8FFFF7BBFE6FF112838993F95D0FF8AD7F5FF43A1D8FFDDFD
      FFFFDAFAFFFFDBFAFFFFDEFAFFFF73DCFCFF75DBFAFF74DAFAFF73DAFAFF73DA
      FAFF71D9FAFFA1E8FFFF7BBFE6FF112838993F95D0FF8AD7F5FF43A1D8FFDDFD
      FFFFDAFAFFFFDBFAFFFFDEFAFFFF73DCFCFF75DBFAFF74DAFAFF73DAFAFF73DA
      FAFF71D9FAFFA1E8FFFF7BBFE6FF1128389900000000885B28FFBA9864FF956C
      36FFFFFFFFFFFFFFFFFF8D6024FF936830FF8D6024FFFFFFFFFFFFFFFFFF956C
      36FFBA9864FF885B28FF00000000000000003D94D0FFABF0FFFF439DD6FF358C
      CBFF358CCBFF358CCBFF368BCBFF5BBEEAFF6ED9FBFF69D6FAFF67D5F9FF66D4
      F9FF65D4F9FF82DEFCFFAAE0F6FF2F71A1EC3D94D0FFC7E9F0FF439DD6FF358C
      CBFF358CCBFF358CCBFF368BCBFF5BBEEAFF6ED9FBFF69D6FAFF67D5F9FF66D4
      F9FF65D4F9FF82DEFCFFAAE0F6FF2F71A1EC3D94D0FFD5F7FFFF439DD6FF358C
      CBFF358CCBFF358CCBFF368BCBFF5BBEEAFF6ED9FBFF69D6FAFF67D5F9FF66D4
      F9FF65D4F9FF82DEFCFFAAE0F6FF2F71A1EC00000000885B28FFBC9C69FF946A
      35FF8B5D22FFFFFFFFFFCBB89DFF8A5C20FFCBB89DFFFFFFFFFF8B5D22FF946A
      35FFBC9C69FF885B28FF00000000000000003C92CFFFB9F4FFFFB9EDFDFF0000
      00FFD8D8D8FFE2E2E2FF000000FF469CD4FF55BAE9FFDAF8FFFFD7F6FFFFD6F6
      FFFFD5F6FFFFD5F7FFFFDBFCFFFF3D94D0FF3C92CFFFCEEBF0FF000000FFB9B9
      B9FF868686FF757575FF8E8E8EFF469CD4FF55BAE9FFDAF8FFFFD7F6FFFFD6F6
      FFFFD5F6FFFFD5F7FFFFDBFCFFFF3D94D0FF3C92CFFFDCF9FFFF000000FFFFE2
      AFFFFFE2AFFFFFE4AEFFB2D0C9FF469CD4FF55BAE9FFDAF8FFFFD7F6FFFFD6F6
      FFFFD5F6FFFFD5F7FFFFDBFCFFFF3D94D0FF00000000885B28FFC1A06DFF9368
      33FFD2C0AAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD1BFAAFF9267
      32FFC1A06DFF885B28FF00000000000000003B92CFFFC0F3FFFFDBF5FEFF0000
      00FF000000FF000000FF000000FFDCF5FDFF439CD4FF368CCBFF358CCBFF348C
      CCFF338DCCFF3790CEFF3C94D0FF4196CEFD3B92CFFFD1EAF0FF000000FFB0B0
      B0FF707070FF777777FF5F5F5FFF858585FF439CD4FF368CCBFF358CCBFF348C
      CCFF338DCCFF3790CEFF3C94D0FF4196CEFD3B92CFFFDFF9FFFF000000FFFFDD
      A7FFFFDDA8FFFFDFA7FFB7CBBEFF3CA6EAFF439CD4FF368CCBFF358CCBFF348C
      CCFF338DCCFF3790CEFF3C94D0FF4196CEFD00000000885B28FFC4A372FF9167
      33FF8E622CFFD2C0A9FF86571CFFFFFFFFFF845419FFCEBCA5FF8B5E28FF8E64
      2FFFC3A270FF875B27FF00000000000000003A92CFFFCAF6FFFFD9F4FDFFBCD3
      DBFFAEC3CAFFADC3CAFFBCD3DBFFF6FCFEFFBCD3DBFFACC0C8FFACC0C8FFB8CF
      D8FFECF8FDFF3C94D0FF0A182169000000003A92CFFFD6ECF0FF000000FFB9B9
      B9FF878787FF595959FF747474FFA5A5A5FFC6C6C6FFC7C7C7FF878787FFC2C2
      C2FF000000FF90BBD9FF0A182169000000003A92CFFFE4FAFFFF000000FFFFDA
      9CFFFFDA9EFFFFDA9EFFFFDD9AFF71ACC5FF0B87E6FF0785E6FFF0DA97FF0000
      00FFB4E3F8FF3C94D0FF0A1821690000000000000000875B27FFC8A776FF9065
      32FF916732FF906530FF8F632EFF8C5F29FF9F7742FFC3A06CFFC4A26FFFC4A2
      70FFC6A473FF875A27FF00000000000000003A92CFFFD5F7FFFFD7F3FDFF0000
      00FF000000FF000000FF000000FFF5FDFFFF000000FF000000FF000000FF0000
      00FFEFFFFFFF3D95D0FF02060833000000003A92CFFFDCECF0FF000000FFB2B2
      B2FF6E6E6EFF717171FF989898FFABABABFF9E9E9EFF898989FF7E7E7EFFBABA
      BAFF000000FF90BCD9FF02060833000000003A92CFFFEAFBFFFF000000FFBDCE
      AFFFC4D0AEFFE4D4A1FFFFD793FFE9DFCBFF000000FF000000FF000000FF0000
      00FFE0FFFFFF3D95D0FF020608330000000000000000875A27FFCAAB7AFF8E62
      2FFF916633FF926633FF916532FF8D612EFFC9A977FF9A713DFF7D4E17FF7C4D
      17FFC8A875FF875A27FF00000000000000003C94D0FFDCFCFFFFF5FDFFFF0000
      00FFD7D7D7FFCBCBCBFF000000FFCEE4F3FF000000FFCECECEFFBFBFBFFF0000
      00FF9EC9E7FF2F6C95D700000000000000003C94D0FFDFEFF0FF000000FFB3B3
      B3FF4F4F4FFF787878FFC1C1C1FF9B9B9BFF929292FF989898FF848484FFBFBF
      BFFF000000FF83A3BAEB00000000000000003C94D0FFEDFDFFFF000000FF21BC
      FFFF30BFFCFF82C8CFFFFFD187FFE9E0D1FF000000FFF3F3F3FFC4CBCFFF0000
      00FF3C94D0FF2F6C95D7000000000000000000000000875A27FFCEAF7DFF8A5E
      2BFF8D622FFF8E6330FF8D622FFF8A5E2BFFCCAD7AFF7D4E17FFF6FFFFFFFFFF
      FFFFAF8955FF3D2912AC00000000000000001F4864B03C94D0FFCEE4F3FF0000
      00FFE0E0E0FFE9E9E9FF000000FFFFFFFFFF000000FFD8D8D8FFE3E3E3FF0000
      00FFFFFFFFFF0000000000000000000000001F4864B090BBD9FF000000FFBFBF
      BFFF929292FFA2A2A2FFC2C2C2FFA6A6A6FFABABABFFAFAFAFFFA3A3A3FFC7C7
      C7FF000000FFE3E3E3FF00000000000000001F4864B09EC9E7FF000000FF6FC8
      D8FF2BC9FFFF67CAD5FFFFCA7AFFF1E8D8FF000000FFBCBCBCF1000000FFFAFA
      FAFF0000000000000000000000000000000000000000875A27FFD1B181FF8457
      23FF875A26FF885B27FF875A26FF845623FFCEAD7CFF7B4C15FFFFFFFFFFAE86
      50FF38250FA70000000000000000000000000000000000000000FFFFFFFF0000
      00FF000000FF000000FF000000FFFFFFFFFF000000FF000000FF000000FF0000
      00FFFFFFFFFF00000000000000000000000000000000E3E3E3FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FFE3E3E3FF000000000000000000000000FFFFFFFF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FFFAFAFAFF0000
      00000000000000000000000000000000000000000000885B28FFD5B687FFD4B5
      85FFD4B586FFD5B586FFD4B586FFD3B485FFD1B282FFD1B281FFB38E58FF3824
      0EA6000000000000000000000000000000000000000000000000FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFF00000000000000000000000000000000E3E3E3FFE3E3E3FFE3E3
      E3FFE3E3E3FFE3E3E3FFE3E3E3FFE3E3E3FFE3E3E3FFE3E3E3FFE3E3E3FFE3E3
      E3FFE3E3E3FFE3E3E3FF000000000000000000000000FFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000
      00000000000000000000000000000000000000000000795326EF885B28FF875A
      27FF875A27FF875A27FF875A27FF865A26FF865926FF875A26FF724C22EA0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000570000005C0000005C0000
      005C0000005C0000005C0000005C0000005C0000005C0000005C0000005C0000
      005C0000005C000000550000000000000000000000570000005C0000005C0000
      005C0000005C0000005C0000005C0000005C0000005C0000005C0000005C0000
      005C0000005C000000550000000000000000000000570000005C0000005C0000
      005C0000005C0000005C0000005C0000005C0000005C0000005C0000005C0000
      005C0000005C000000550000000000000000000000570000005C0000005C0000
      005C0000005C0000005C0000005C0000005C0000005C0000005C0000005C0000
      005C0000005C0000005500000000000000004496CFFE4298D2FF3F94D0FF3D92
      CFFF3D92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92
      CEFF3E93CFFF4092CCFE0000001B000000004496CFFE4298D2FF3F94D0FF3D92
      CFFF3D92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92
      CEFF3E93CFFF4092CCFE0000001B000000004496CFFE4298D2FF3F94D0FF3D92
      CFFF3D92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92
      CEFF3E93CFFF4092CCFE0000001B000000004496CFFE4298D2FF3F94D0FF3D92
      CFFF3D92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92
      CEFF3E93CFFF4092CCFE0000001B000000004399D2FF3E94D0FFABFBFFFF9BF3
      FFFF92F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1
      FFFFA6F8FFFF64B8E3FF1229399B000000004399D2FF3E94D0FFABFBFFFF9BF3
      FFFF92F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1
      FFFFA6F8FFFF64B8E3FF1229399B000000004399D2FF3E94D0FFABFBFFFF9BF3
      FFFF92F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1
      FFFFA6F8FFFF64B8E3FF1229399B000000004399D2FF3E94D0FFABFBFFFF9BF3
      FFFF92F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1
      FFFFA6F8FFFF64B8E3FF1229399B000000004298D2FF4EA6D9FF8EDAF5FFA2EE
      FFFF82E5FEFF84E5FEFF84E5FEFF85E6FEFF85E6FEFF85E6FEFF85E6FEFF84E6
      FEFF96EBFFFF8CD8F5FF30709FEB000000004298D2FF4EA6D9FF8EDAF5FFA2EE
      FFFF82E5FEFF84E5FEFF84E5FEFF85E6FEFF85E6FEFF85E6FEFF85E6FEFF84E6
      FEFF96EBFFFF8CD8F5FF30709FEB000000004298D2FF4EA6D9FF8EDAF5FFA2EE
      FFFF82E5FEFF84E5FEFF84E5FEFF85E6FEFF85E6FEFF85E6FEFF85E6FEFF84E6
      FEFF96EBFFFF8CD8F5FF30709FEB000000004298D2FF4EA6D9FF8EDAF5FFA2EE
      FFFF82E5FEFF84E5FEFF84E5FEFF85E6FEFF85E6FEFF85E6FEFF85E6FEFF84E6
      FEFF96EBFFFF8CD8F5FF30709FEB000000004196D1FF6ABEE8FF6CBDE6FFBBF2
      FFFF74DEFDFF76DEFCFF77DEFCFF7ADFFCFF7CDFFCFF7CDFFCFF7CDFFCFF7BDF
      FCFF80E0FDFFADF0FFFF4C9DD3FF0000001B4196D1FF6ABEE8FF6CBDE6FFBBF2
      FFFF74DEFDFF76DEFCFF77DEFCFF7ADFFCFF7CDFFCFF7CDFFCFF7CDFFCFF7BDF
      FCFF80E0FDFFADF0FFFF4C9DD3FF0000001B4196D1FF6ABEE8FF6CBDE6FFBBF2
      FFFF74DEFDFF76DEFCFF77DEFCFF7ADFFCFF7CDFFCFF7CDFFCFF7CDFFCFF7BDF
      FCFF80E0FDFFADF0FFFF4C9DD3FF0000001B4196D1FF6ABEE8FF6CBDE6FFBBF2
      FFFF74DEFDFF76DEFCFF77DEFCFF7ADFFCFF7CDFFCFF7CDFFCFF7CDFFCFF7BDF
      FCFF80E0FDFFADF0FFFF4C9DD3FF0000001B3F95D0FF8AD7F5FF43A1D8FFDDFD
      FFFFDAFAFFFFDBFAFFFFDEFAFFFF73DCFCFF75DBFAFF74DAFAFF73DAFAFF73DA
      FAFF71D9FAFFA1E8FFFF7BBFE6FF112838993F95D0FF8AD7F5FF43A1D8FFDDFD
      FFFFDAFAFFFFDBFAFFFFDEFAFFFF73DCFCFF75DBFAFF74DAFAFF73DAFAFF73DA
      FAFF71D9FAFFA1E8FFFF7BBFE6FF112838993F95D0FF8AD7F5FF43A1D8FFDDFD
      FFFFDAFAFFFFDBFAFFFFDEFAFFFF73DCFCFF75DBFAFF74DAFAFF73DAFAFF73DA
      FAFF71D9FAFFA1E8FFFF7BBFE6FF112838993F95D0FF8AD7F5FF43A1D8FFDDFD
      FFFFDAFAFFFFDBFAFFFFDEFAFFFF73DCFCFF75DBFAFF74DAFAFF73DAFAFF73DA
      FAFF71D9FAFFA1E8FFFF7BBFE6FF112838993D94D0FFABF0FFFF439DD6FF358C
      CBFF358CCBFF358CCBFF368BCBFF5BBEEAFF6ED9FBFF69D6FAFF67D5F9FF66D4
      F9FF65D4F9FF82DEFCFFAAE0F6FF2F71A1EC3D94D0FFABF0FFFF439DD6FF358C
      CBFF358CCBFF358CCBFF368BCBFF5BBEEAFF6ED9FBFF69D6FAFF67D5F9FF66D4
      F9FF65D4F9FF82DEFCFFAAE0F6FF2F71A1EC3D94D0FFABF0FFFF439DD6FF358C
      CBFF358CCBFF358CCBFF368BCBFF5BBEEAFF6ED9FBFF69D6FAFF67D5F9FF66D4
      F9FF65D4F9FF82DEFCFFAAE0F6FF2F71A1EC3D94D0FFABF0FFFF439DD6FF358C
      CBFF358CCBFF358CCBFF368BCBFF5BBEEAFF6ED9FBFF69D6FAFF67D5F9FF66D4
      F9FF65D4F9FF82DEFCFFAAE0F6FF2F71A1EC3C92CFFFB9F4FFFF72DBFBFF6ACC
      F2FFFFFFFFFF000000FFFFFFFFFF469CD4FF55BAE9FFDAF8FFFFD7F6FFFFD6F6
      FFFFD5F6FFFFD5F7FFFFDBFCFFFF3D94D0FF3C92CFFFB9F4FFFFFFFFFFFF0000
      00FF000000FF000000FFFFFFFFFF469CD4FF55BAE9FFDAF8FFFFD7F6FFFFD6F6
      FFFFD5F6FFFFD5F7FFFFDBFCFFFF3D94D0FF3C92CFFFB9F4FFFF72DBFBFF6ACC
      F2FFFFFFFFFFFFFFFFFF000000FF469CD4FF55BAE9FFDAF8FFFFD7F6FFFFD6F6
      FFFFD5F6FFFFD5F7FFFFDBFCFFFF3D94D0FF3C92CFFFB9F4FFFF72DBFBFFFFFF
      FFFF000000FFFFFFFFFF6CCEF3FF469CD4FF55BAE9FFDAF8FFFFD7F6FFFFD6F6
      FFFFD5F6FFFFD5F7FFFFDBFCFFFF3D94D0FF3B92CFFFC0F3FFFF70DAFBFF73DB
      FBFF74DBFCFFFFFFFFFF000000FFFFFFFFFF439CD4FF368CCBFF358CCBFF348C
      CCFF338DCCFF3790CEFF3C94D0FF4196CEFD3B92CFFFC0F3FFFFFFFFFFFF0D1A
      1EFF000000FF000000FFFFFFFFFF000000FF439CD4FF368CCBFF358CCBFF348C
      CCFF338DCCFF3790CEFF3C94D0FF4196CEFD3B92CFFFC0F3FFFFFFFFFFFFFFFF
      FFFFFFFFFFFF000000FF000000FFFFFFFFFF439CD4FF368CCBFF358CCBFF348C
      CCFF338DCCFF3790CEFF3C94D0FF4196CEFD3B92CFFFC0F3FFFF70DAFBFFFFFF
      FFFFFFFFFFFFFFFFFFFF4C656DFF72DAFAFF439CD4FF368CCBFF358CCBFF348C
      CCFF338DCCFF3790CEFF3C94D0FF4196CEFD3A92CFFFCAF6FFFF68D5F9FF6BD5
      F9FFFFFFFFFF000000FF000000FF000000FF000000FF000000FFFFFFFFFF5CC8
      F2FFB4E3F8FF3C94D0FF0A182169000000003A92CFFFCAF6FFFFFFFFFFFFFFFF
      FFFFFFFFFFFF000000FFFFFFFFFF173039FF000000FF000000FFFFFFFFFF5CC8
      F2FFB4E3F8FF3C94D0FF0A182169000000003A92CFFFCAF6FFFFFFFFFFFF0000
      00FF000000FF000000FF000000FFFFFFFFFF111732FF10142EFFFFFFFFFF5CC8
      F2FFB4E3F8FF3C94D0FF0A182169000000003A92CFFFCAF6FFFF68D5F9FF6BD5
      F9FF49636CFF68D5F9FF68D5FAFF69D7FBFF48636CFF5DC7F1FF46606AFF5CC8
      F2FFB4E3F8FF3C94D0FF0A182169000000003A92CFFFD5F7FFFF5FD1F9FF60D0
      F8FFFFFFFFFF000000FFFFFFFFFF000000FFFFFFFFFF000000FFFFFFFFFFDCFB
      FFFFE0FFFFFF3D95D0FF02060833000000003A92CFFFD5F7FFFF5FD1F9FF60D0
      F8FFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFDCFB
      FFFFE0FFFFFF3D95D0FF02060833000000003A92CFFFD5F7FFFFFFFFFFFF0000
      00FF000000FF000000FF000000FFFFFFFFFFFFFFFFFF000000FFFFFFFFFFDCFB
      FFFFE0FFFFFF3D95D0FF02060833000000003A92CFFFD5F7FFFF5FD1F9FF4762
      6CFFB4EBFDFF646B6EFFDAF8FFFFDAF8FFFFDBF9FFFF656C6EFFDCFAFFFFDCFB
      FFFFE0FFFFFF3D95D0FF02060833000000003C94D0FFDCFCFFFFD8F7FFFFD8F7
      FFFFDBFAFFFFFFFFFFFF000000FF000000FF000000FFFFFFFFFF3992CFFF3A92
      CFFF3C94D0FF2F6C95D700000000000000003C94D0FFDCFCFFFFD8F7FFFFD8F7
      FFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFF3A92
      CFFF3C94D0FF2F6C95D700000000000000003C94D0FFDCFCFFFFFFFFFFFF0000
      00FF000000FF000000FF000000FFFFFFFFFF111733FF121731FFFFFFFFFF3A92
      CFFF3C94D0FF2F6C95D700000000000000003C94D0FFDCFCFFFFD8F7FFFFFFFF
      FFFFFFFFFFFFFFFFFFFF3891CEFF3D5362FFFFFFFFFFFFFFFFFFFFFFFFFF3A92
      CFFF3C94D0FF2F6C95D700000000000000001F4864B03C94D0FF3992CFFF3992
      CFFF3C94D0FF2C658DD2FFFFFFFF000000FFFFFFFFFF00000000000000000000
      0000000000000000000000000000000000001F4864B03C94D0FF3992CFFF3992
      CFFFFFFFFFFF000000FF000000FF000000FC000000FF000000FFFFFFFFFF0000
      0000000000000000000000000000000000001F4864B03C94D0FFFFFFFFFFFFFF
      FFFFFFFFFFFF000000FF000000FFFFFFFFFF000000FFFFFFFFFFFFFFFFFF0000
      0000000000000000000000000000000000001F4864B03C94D0FF3992CFFFFFFF
      FFFF000000FFFFFFFFFF242424C000000000FFFFFFFF000000FFFFFFFFFF0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FFFFFFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFFFFBDBDBDFF9F9F9FFF454545FF000000F8000000FFFFFFFFFF0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFF000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FFFFFFFFFFFFFFFFFFFF00000000242424C0FFFFFFFFFFFFFFFFFFFFFFFF0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000300000000000000030000
      0000000000000000000300000000000000030000000000000000000000030000
      0000000000030000000000000000000000020000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000A000000000000
      000700000002000000000000000A000000000000000700000002000000000000
      000A000000000000000700000002000000000000003000000033000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000003300000033000000300000003000000033000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002F0000000000000000000000570000005C0000005C0000
      005C0000005C0000005C0000005C0000005C0000005C0000005C0000005C0000
      005C0000005C0000005500000000000000004040408040404080414141854040
      4080404040834141418140404080414141854040408040404083414141814040
      4080414141854040408040404083404040803986BBF13595D7FF3595D7FF3595
      D7FF3595D7FF3595D7FF3595D7FF3595D7FF3595D7FF3595D7FF3595D7FF3595
      D7FF3595D7FF3595D7FF3594D7FF3986BBF13D89BCF24298D2FF3F94D0FF3D92
      CFFF3D92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92
      CEFF3E93CFFF3983B6F00000000E000000004496CFFE4298D2FF3F94D0FF3D92
      CFFF3D92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92
      CEFF3E93CFFF4092CCFE0000001B0000000040404080575757E85D5C5BFF6B6A
      68FF868582FF868582FF868582FF868582FF868582FF868582FF868582FF8685
      82FF6B6A68FF5D5C5BFF575757E8404040803F95D1FF91FBFFFF91FBFFFF91FB
      FFFF91FBFFFF91FBFFFF91FBFFFF91FBFFFF91FBFFFF91FBFFFF91FBFFFF91FB
      FFFF91FBFFFF91FBFFFFA0FEFFFF3E94D1FF4399D2FF3E94D0FFABFBFFFF9BF3
      FFFF92F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1
      FFFFA6F8FFFF64B8E3FF060F155F000000004399D2FF3E94D0FFABFBFFFF9BF3
      FFFF92F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1
      FFFFA6F8FFFF64B8E3FF1229399B00000000404040805D5C5BFF5D5C5BFF6A69
      68FF706F6DFF767573FF868582FF868582FF868582FF868582FF767573FF706F
      6DFF6B6A68FF5D5C5BFF5D5C5BFF404040803D93D0FF88F4FFFF88F4FFFF88F4
      FFFF88F4FFFF88F4FFFF88F4FFFF88F4FFFF88F4FFFF88F4FFFF88F4FFFF88F4
      FFFF88F4FFFF88F4FFFF9FF8FFFF3C93D0FF4298D2FF4EA6D9FF8EDAF5FFA2EE
      FFFF82E5FEFF84E5FEFF84E5FEFF85E6FEFF85E6FEFF85E6FEFF85E6FEFF84E6
      FEFF96EBFFFF8CD8F5FF1D4562B8000000004298D2FF4EA6D9FF8EDAF5FFA2EE
      FFFF82E5FEFF84E5FEFF84E5FEFF85E6FEFF85E6FEFF85E6FEFF85E6FEFF84E6
      FEFF96EBFFFF8CD8F5FF30709FEB00000000404040805D5C5BFF5D5C5BFF5D5C
      5BFF5D5C5BFF5D5C5BFF5D5C5BFF5D5C5BFF5D5C5BFF5D5C5BFF5D5C5BFF5D5C
      5BFF5D5C5BFF5D5C5BFF5D5C5BFF404040803E93D0FF82EDFFFF82EDFFFF82ED
      FFFF82EDFFFF82EDFFFF82EDFFFF82EDFFFF82EDFFFF82EDFFFF82EDFFFF82ED
      FFFF82EDFFFF82EDFFFFA2F5FFFF3C92D0FF4196D1FF6ABEE8FF6CBDE6FFBBF2
      FFFF74DEFDFF76DEFCFF77DEFCFF7ADFFCFF7CDFFCFF7CDFFCFF7CDFFCFF7BDF
      FCFF80E0FDFFADF0FFFF4C9DD3FF0000000E4196D1FF6ABEE8FF6CBDE6FFBBF2
      FFFF74DEFDFF76DEFCFF77DEFCFF7ADFFCFF7CDFFCFF7CDFFCFF7CDFFCFF7BDF
      FCFF80E0FDFFADF0FFFF4C9DD3FF0000001B404040805D6466FF61D4FBFF61D4
      FBFF61D4FBFF61D4FBFF61D4FBFF61D4FBFF61D4FBFF61D4FBFF61D4FBFF61D4
      FBFF61D4FBFF61D4FBFF5D6466FF404040803E93CFFF7CE8FFFF7CE8FFFF7CE8
      FFFF7CE8FFFF7CE8FFFF7CE8FFFF7CE8FFFF7CE8FFFF7CE8FFFF7CE8FFFF7CE8
      FFFF7CE8FFFF7CE8FFFFA8F2FFFF3C92CFFF3F95D0FF8AD7F5FF43A1D8FFDDFD
      FFFFDAFAFFFFDBFAFFFFDEFAFFFF73DCFCFF75DBFAFF74DAFAFF73DAFAFF73DA
      FAFF71D9FAFFA1E8FFFF7BBFE6FF060F155E3F95D0FF8AD7F5FF43A1D8FFDDFD
      FFFFDAFAFFFFDBFAFFFFDEFAFFFF73DCFCFF75DBFAFF74DAFAFF73DAFAFF73DA
      FAFF71D9FAFFA1E8FFFF7BBFE6FF11283899404040805C6266FF5BBFFEFF5BBF
      FEFFA5D7F5FFF0EFEBFFF1F0EBFFF1F0EBFFF2F0EBFFF1F0EBFFF0EFEBFFA6D7
      F5FF5BBFFFFF5BBFFEFF5C6367FF404040803E93CFFF75E1FFFF75E1FFFF75E1
      FFFF75E1FFFF75E1FFFF75E1FFFF75E1FFFF75E1FFFF75E1FFFF75E1FFFF75E1
      FFFF75E1FFFF75E1FFFFAFEFFFFF3C92CFFF3D94D0FFABF0FFFF439DD6FF358C
      CBFF358CCBFF358CCBFF368BCBFF5BBEEAFF6ED9FBFF69D6FAFF67D5F9FF66D4
      F9FF65D4F9FF82DEFCFFAAE0F6FF1D4563B93D94D0FFABF0FFFF439DD6FF358C
      CBFF358CCBFF358CCBFF368BCBFF5BBEEAFF6ED9FBFF69D6FAFF67D5F9FF66D4
      F9FF65D4F9FF82DEFCFFAAE0F6FF2F71A1EC404040805C6266FF5BBFFFFF91D0
      F7FFA8A6A3FF7E7C7BFFDDDBD7FF8E8C89FF676665FFDDDBD7FF7E7C7BFFA7A5
      A2FF91D0F7FF5BBFFEFF5C6367FF404040803D94D0FFE1FFFFFFDAFAFFFFD9F9
      FFFFD9FAFFFFDCFAFFFF6DDAFDFF6FD9FCFF6FD8FBFF6ED8FBFF6ED8FBFF6ED8
      FBFF6ED8FBFF6BD8FBFFB5EFFFFF3C92CFFF3C92CFFFB9F4FFFF72DBFBFF6ACC
      F2FF6BCDF3FF6BCEF3FF6CCEF3FF469CD4FF55BAE9FFDAF8FFFFD7F6FFFFD6F6
      FFFFD5F6FFFFD5F7FFFFDBFCFFFF3D94D0FF3C92CFFFB9F4FFFF72DBFBFFB5E5
      F8FF000000FFFFFFFFFFFFFFFFFF469CD4FF55BAE9FFDAF8FFFFD7F6FFFFD6F6
      FFFFD5F6FFFFD5F7FFFFDBFCFFFF3D94D0FF404040805C6266FF5BBFFEFF91D0
      F7FFBCBAB6FF8D8C89FFDDDBD7FF8E8C89FF676665FFDDDBD7FF8D8C89FFBBBA
      B6FF91D0F7FF5BBFFEFF5C6367FF404040803F95D1FF368ECDFF338BCBFF348B
      CBFF358BCAFF368ACAFF5ABBEAFF6BD6FBFF67D4FAFF65D2F9FF64D2F9FF64D2
      F9FF64D2F9FF62D2FAFFB9F0FFFF3B92CFFF3B92CFFFC0F3FFFF70DAFBFF73DB
      FBFF74DBFCFF74DBFCFF75DCFCFF72DAFAFF439CD4FF368CCBFF358CCBFF348C
      CCFF338DCCFF3790CEFF3C94D0FF3881B3EB3B92CFFFC0F3FFFF70DAFBFFB9ED
      FDFF000000FFFFFFFFFFFFFFFFFFFFFFFFFF439CD4FF368CCBFF358CCBFF348C
      CCFF338DCCFF3790CEFF3C94D0FF4196CEFD404040805C6266FF5BBFFEFF83CB
      F9FFDEE9EDFFF2F0EBFFF2F0EBFFF2F0EBFFF2F0EBFFF2F0EBFFF2F0EBFFDEE9
      EDFF83CBF9FF5BBFFFFF5C6367FF404040803D94D0FFC8F8FFFF71DDFEFF74DD
      FDFF75DEFDFF75DEFEFF4EAADCFF53B8E8FFD9F7FFFFD5F6FFFFD5F6FFFFD5F6
      FFFFD4F5FFFFD4F6FFFFD9FBFFFF3C94D0FF3A92CFFFCAF6FFFF68D5F9FF6BD5
      F9FF6AD5F9FF68D5F9FF68D5FAFF69D7FBFF67D4FAFF5DC7F1FF5DC7F2FF5CC8
      F2FFB4E3F8FF3C94D0FF0A182169000000003A92CFFFCAF6FFFF68D5F9FFB5EA
      FCFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFF000000FF9EC9E7FF0A18216900000000404040805D6466FF60D3FAFF61D3
      FAFF61D3FAFF61D4FBFF60D3FAFF60D3FAFF61D4FAFF61D4FBFF60D4FAFF60D4
      FAFF61D4FAFF61D4FAFF5D6466FF404040803A92CFFFCEF7FFFF68D5FAFF6CD5
      FAFF6CD5FAFF6AD5FAFF6AD8FCFF46A8DDFF308ACBFF2E8ACBFF2E8ACBFF2E8A
      CBFF2E8ACBFF2F8BCBFF348FCDFF3F95D1FF3A92CFFFD5F7FFFF5FD1F9FF60D0
      F8FFB4EBFDFFD9F6FFFFDAF8FFFFDAF8FFFFDBF9FFFFDCFAFFFFDCFAFFFFDCFB
      FFFFE0FFFFFF3D95D0FF02060833000000003A92CFFFD5F7FFFF5FD1F9FFB0E7
      FBFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FF000000FF0000
      00FF000000FF9ECAE7FF0206083300000000404040805D6466FF60D4FAFF60D4
      FAFF61D4FAFF61D4FAFF61D4FBFF60D3FAFF61D3FAFF61D3FAFF61D4FBFF60D3
      FAFF60D3FAFF61D4FBFF5D6466FF404040803A92CFFFD5F8FFFF5FD1F9FF62D1
      F8FF61D1F8FFB5EBFDFFDAF8FFFFDCFBFFFFDDFDFFFFDDFDFFFFDDFDFFFFDDFD
      FFFFDDFDFFFFDDFEFFFFE3FFFFFF3F96D1FF3C94D0FFDCFCFFFFD8F7FFFFD8F7
      FFFFDBFAFFFF348ECDFF3891CEFF3992CFFF3992CFFF3992CFFF3992CFFF3A92
      CFFF3C94D0FF2F6C95D700000000000000003C94D0FFDCFCFFFFD8F7FFFFEBFB
      FFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFF
      FFFF000000FF90B1C7EB0000000000000000404040805D5C5BFF5D5C5BFF5D5C
      5BFF5D5C5BFF5D5C5BFF5D5C5BFF5D5C5BFF5D5C5BFF5D5C5BFF5D5C5BFF5D5C
      5BFF5D5C5BFF5D5C5BFF5D5C5BFF404040803C94D0FFDCFCFFFFD8F8FFFFD9F7
      FFFFD9F7FFFFDBFAFFFF348ECDFF3992CFFF3A92CFFF3A93CFFF3A93CFFF3A93
      CFFF3A93CFFF3A93D0FF3D95D0FF1F4864B01F4864B03C94D0FF3992CFFF3992
      CFFF3C94D0FF2C658DD200000000000000000000000000000000000000000000
      0000000000000000000000000000000000001F4864B03C94D0FF3992CFFF9CC8
      E7FF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFF0000
      00FFE1E1E1F0C4C4C4E000000000000000004040408040404083414141814040
      4080414141854040408040404083414141814040408041414185404040804040
      408341414181404040804141418540404080285A7DC53C94D0FF3992CFFF3992
      CFFF3992CFFF3C94D0FF235273BD000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FFFF000000FF000000FF000000FF000000FF000000FF000000FF000000FFF1F1
      F1F8C4C4C4E00000000000000000000000000000000A00000000000000070000
      0002000000000000000A000000000000000700000002000000000000000A0000
      0000000000070000000200000000000000030000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC4C4
      C4E000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000800000000100010000000000000400000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000}
  end
  object dlgOpen: TOpenTextFileDialog
    DefaultExt = 'agdx'
    Filter = 'AGDX Project|*.agdx|All Files|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Title = 'Open an Existing AGDX Project'
    Left = 420
    Top = 88
  end
  object popProject: TPopupMenu
    OnClose = popProjectClose
    OnPopup = popProjectPopup
    Left = 120
    Top = 88
    object mnuNewAsset: TMenuItem
      Action = actFileNewImageDefault
      ImageName = 'asterisk_orange'
    end
    object DuplicateImage1: TMenuItem
      Action = actEditDuplicateImage
    end
    object DeleteAsset1: TMenuItem
      Action = actDeleteAsset
    end
    object Replace1: TMenuItem
      Action = actEditSplitIntoTiles
    end
  end
  object imgBuildNodes: TImageList
    ColorDepth = cd32Bit
    Left = 118
    Top = 256
    Bitmap = {
      494C01010E001800040010001000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000004000000001002000000000000040
      0000000000000000000000000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002300000000000000000000000000000000000000000000
      0000000000000000000000000000000000330000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000005C5C5BC0B0B0ADFFAFAF
      ACFFAEAEABFFADADABFFADADABFFADADABFFADADABFFADADABFFADADABFFAEAE
      ABFFAFAFADFF5C5C5BC000000000000000000000000000000000000000000000
      00000000000000000000000000331D72A8FF0000003300000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B0B0ADFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFB0B0ADFF00000000000000000000000000000000000000000000
      000000000000000000331A6CA4FF65F0FFFF1A6CA3FF00000033000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B0B0ACFFFFFFFFFF0010
      DBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFE
      FEFFFFFFFFFFAEAEABFF00000000000000000000000000000000000000000000
      0000000000331A6CA3FF62E8FFFF54E0FFFF62E7FFFF196BA2FF000000330000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B0B0ABFFFFFFFFFF5682
      EAFFFFFFFDFF989795FFC1C1C1FFFFFEFEFF979797FFC2C2C2FFBFC0C0FFFCFB
      FBFFFFFFFFFFADADABFF00000000000000000000000000000000000000000000
      00331A6CA3FF4CC4F0FF4EDBFFFF4CDAFFFF4DDAFFFF65E6FFFF196BA2FF0000
      0033000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B0AFABFFFFFFFFFF0012
      DBFFFFFFF9FFFDFCFAFFFAFAFAFFF9F9F9FFFAFAFBFFFAFAFBFFF9F9F9FFF8F8
      F8FFFFFFFFFFADADABFF00000000000000000000000000000000000000331A6C
      A3FF69E6FFFF4AD5FFFF49D7FFFF461C10FF48D6FFFF49D4FFFF69E5FFFF1A6C
      A3FF000000330000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000AFAFABFFFFFFFFFFFFFF
      F5FFFFFDF4FFF7F7F5FFF6F6F5FFF5F5F4FFF6F6F4FFF6F6F5FFF5F5F4FFF4F4
      F3FFFFFFFFFFADADABFF000000000000000000000000000000331A6CA3FF4DC1
      F0FF43D1FFFF43CEFFFF43D4FFFF39A1CAFF43D4FFFF43CEFFFF43D0FFFF4DC1
      F0FF1A6CA3FF0000003300000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B0AFABFFFFFFFFFF0012
      DBFFFFFCF2FFF7F7F4FFF5F5F4FFF4F4F3FFF4F4F2FFF4F5F3FFF4F4F2FFF2F2
      F1FFFFFFFFFFADADABFF000000000000000000000033186CA3FF6EE2FFFF3DCC
      FFFF3EC9FFFF3ECAFFFF3CD1FFFF644132FF3CD1FFFF3ECAFFFF3EC9FFFF3DCC
      FFFF6EE2FFFF186CA3FF00000033000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B0B0ABFFFFFFFFFF527D
      E4FFFFFCF1FF9C9C9AFFBFBFBFFFBEBEBEFFF4F3F3FF989898FFBDBDBDFFF0EF
      F0FFFFFFFFFFADADABFF00000000000000001B72A8FF9BF5FFFF35C8FFFF38C4
      FFFF3AC4FFFF3AC6FFFF38CEFFFF59392CFF38CEFFFF3AC6FFFF3AC4FFFF38C4
      FFFF35C8FFFF9BF5FFFF1B72A8FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B0AFABFFFFFFFFFF0013
      DDFFFCF7EDFFF3F1EEFFF1F0EFFFF0EFEDFFEFEEEDFFF0EEEDFFEFEEECFFEDEC
      EAFFFFFFFFFFADADABFF000000000000000000000000186CA3FF77E0FFFF31C1
      FFFF33C0FFFF34C2FFFF33CBFFFF4F2F23FF33CBFFFF34C2FFFF33C0FFFF31C1
      FFFF77E0FFFF186CA3FF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000AFAFABFFFFFFFFFFFDF8
      E9FFF5F2EAFFEDEDEAFFEBEBEAFFEAEAE9FFF4F4F3FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFAEAEABFF00000000000000000000000000000000196CA2FF7BDF
      FFFF2BBDFFFF2EBEFFFF2EC7FFFF442518FF2EC6FFFF2DBEFFFF2BBDFFFF7BDF
      FFFF196CA2FF0000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B0AFABFFFFFFFFFF0014
      DDFFF7F2E7FFEEECE9FFEAE9E8FFE8E6E5FFFFFFFFFFCBCBCAFFA7A7A4FFA5A5
      A3FFFFFFFFFFAFAFADFF0000000000000000000000000000000000000000196D
      A2FF7DDFFFFF28BBFFFF29C0FFFF3A1606FF29C0FFFF26BAFFFF7CDEFFFF196C
      A2FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B0B0ABFFFFFFFFFF4E78
      E0FFF5F0E6FF9D9C9BFFBABAB9FFE5E4E4FFFFFFFFFFA7A7A4FFEBEAEAFFFFFF
      FFFFE9E9E9FF4F4F4EAC00000000000000000000000000000000000000000000
      00001A6EA3FF51B8F1FF21B9FFFF22BAFFFF20B8FFFF81DDFFFF196CA2FF0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B0B0ACFFFFFFFFFF0012
      DDFFEEEAE0FFE6E5E2FFE3E2E1FFE1DFDEFFFFFFFFFFA5A5A3FFFFFFFFFFE8E8
      E8FF4B4B49A70000000000000000000000000000000000000000000000000000
      0000000000001A6EA3FF83DCFFFF15B2FFFF82DBFFFF196DA2FF000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B0B0ADFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE9E9E9FF4949
      48A6000000000000000000000000000000000000000000000000000000000000
      00000000000000000000176DA4FFD0F9FFFF176DA3FF00000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000009D9D9BEFB0B0ADFFB0AF
      ACFFAFAEABFFAEAEABFFAEAEABFFADAEABFFAEAEABFFAFAFADFF949493EA0000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000001A72A8FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000001E00000031000000330000003300000033000000310000001E0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000030000000330000003300000033000000330000
      0033000000330000003300000033000000300000000000000000000000000000
      00000000000000000000000000000000002A000000330000002A000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000E0000
      0033452B0AAAA96816F9B26E17FFB26E17FFB26E17FFA96816F9452B0AAA0000
      00330000000E0000000000000000000000000000000000000000000000000000
      00000000000000000000A57727F2B68123FFB57E1FFFB57E1EFFB57E1EFFB57E
      1EFFB57E1EFFB57E1FFFB68123FFA57727F20000000000000000000000000000
      000000000000000000000000002D795632DDA77644FF795632DD0000002D0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000E140C036BB26D
      15FFC27B2AFFD08637FFD48939FFD48939FFD48939FFD08637FFC27B2AFFB26D
      15FF140C036B0000000E00000000000000000000000000000000000000000000
      00000000000000000000B68224FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFB68123FF0000000000000000000000000000
      0000000000000000002D865F36E9C5A37DFFFBF4E7FFC5A37DFF865F36E90000
      002D000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000140C036BB46E17FFD089
      3AFFDCB380FFE4F4EDFFEBFFFFFF9AABB2FFEBFFFFFFE4F4EDFFDCB380FFD089
      3AFFB46E17FF140C036B00000000000000000000003000000033000000330000
      00330000003300000033B58021FFFFFFFFFFEADDBAFFEADCB8FFE8D9B3FFE7D7
      B1FFE6D6AFFFE6D6AEFFFFFFFFFFB57E1EFF0000000000000000000000000000
      00000000002D855F36E8C4A47EFFF6EDDFFFC19E78FFF6EDDFFFC4A47EFF855F
      36E80000002D0000000000000000000000000000002300000033000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000003300000033000000230000001EB16C14FFD48D41FFDECC
      ACFFE2FFFFFFE1FFFFFFE2FFFFFFE3FFFFFFE2FFFFFFE1FFFFFFE2FFFFFFDECC
      ACFFD48D41FFB16C14FF0000001E00000000A57727F2B68123FFB57E1FFFB57E
      1EFFB57E1EFFB47D1DFFB37A19FFB07611FFB07511FFBB8A31FFEADCB8FFE7D7
      B1FFE6D6AFFFE5D5ACFFFFFFFFFFB47D1DFF0000000000000000000000000000
      002D855F36E8C5A581FFF8F1E6FFB4895CFFA3713DFFB4895CFFF8F1E6FFC5A5
      81FF855F36E80000002D00000000000000004C4C4EC08F9297FF8D9299FF8D93
      9BFF8D939BFF8D929AFF8D9299FF8D929AFF8D9197FF8C8D8FFF8B8B8BFF8A8A
      8AFF8A8A8AFF8B8B8BFF8D8D8DFF4B4B4BC0452B09A9C98434FFDDB98BFFDCFF
      FFFFDBFBFFFFDBF9FDFFDCFAFDFFDCF9FDFFDBF8FCFFDBF9FCFFDBFBFFFFDCFF
      FFFFDDB98BFFC98434FF452B09A900000000B68123FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB0750FFFFCFBF4FFF9F4
      E9FFF8F2E6FFF8F2E5FFFFFFFFFFB47D1DFF00000000000000000000002D855F
      36E8C7A684FFFAF4EAFFB3895BFFA26F3BFFA3703CFFA26F3BFFB3895BFFFAF4
      EAFFC7A684FF855F36E80000002D000000008F9297FFF8C479FFF2BE75FFDB99
      3FFFDB9941FFF1C078FFF1BF77FFDB9A41FFDC983BFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFF8D8D8DFFA96714F9DD9A51FFD9F0ECFFD6FB
      FFFFD6F8FBFFD8F9FCFFDBFDFFFFDAFCFFFFD8F8FBFFD6F6F9FFD6F7FAFFD6FB
      FFFFD9F0ECFFDD9A51FFA96714F900000000B57E1EFFFFFFFFFFE6D6AEFFE6D6
      AFFFE6D7B0FFE6D7B0FFE6D6AFFFE6D6AEFFFFFFFFFFAE730DFFF8F5E7FFF4EE
      DCFFF3ECD9FFF3ECD8FFFFFFFFFFB47D1DFF0000000000000026865E35E9C6A7
      84FFFCF7EFFFB38A5EFFB89167FFFAF2E4FFF8EFE0FFFBF3E6FFB99268FFB38B
      5EFFFCF7EFFFC6A784FF865E35E90000002A8D9197FFE6B26BFFEFC383FFEEC4
      86FFD79C4CFFD79C4CFFEEC486FFEDC283FFDA9F4BFFF6FAFFFFF5F5F6FFF5F4
      F4FFF5F4F4FFF6F5F5FFFFFFFFFF8B8C8CFFB16C14FFE9A662FFD3FFFFFFD2F6
      FDFFD2F5FAFFD7FBFFFF534846FFB3CCCEFFD6FAFFFFD2F5FAFFD1F3F9FFD2F6
      FDFFD3FFFFFFE9A662FFB16C14FF00000000B47D1DFFFFFFFFFFE5D5ACFFE6D6
      AFFFE6D6AFFFE6D6AFFFE6D6AFFFE5D5ACFFFFFFFFFFAE730DFFF6F0DEFFF1E8
      D1FFF0E6CDFFF0E7CDFFFFFFFFFFB47D1DFF0000000064472ACCC8A887FFFDF9
      F2FFB58C5FFFA67542FFA57441FFB89065FFFDF8EFFFA26E39FFA77644FFA675
      43FFB58C5FFFFDF9F2FFC8A887FF785632DD8C9095FFF0C792FFD89E4CFFF1C8
      8EFFF1C98EFFD9A053FFD9A053FFF1C78CFFF0C281FFEBEFF4FFEBEAEBFFEBEA
      E9FFEBEAE9FFEBEAE9FFFCFBFBFF8B8C8CFFB16C13FFEEAD69FF7E959EFFCEF6
      FCFFCEF4F9FFD4FCFFFFB5D0D4FF594F4DFFADC5C8FFCEF4F9FFCDF2F7FFCEF6
      FCFF7E959EFFEEAD69FFB16C13FF00000000B47D1DFFFFFFFFFFF8F2E5FFF8F2
      E6FFF8F3E7FFF8F3E7FFF8F2E6FFF8F2E5FFFFFFFFFFAE730DFFF1EAD3FFF7F1
      E4FFFFFFFFFFFFFFFFFFFFFFFFFFB47E1DFF00000000A67442FFFFFFFFFFC4A4
      81FFA3713DFFA87746FFA67441FFB99166FFFFFFFEFFA4713DFFA97949FFA979
      48FFA4713DFFC4A481FFFFFFFFFFA67442FF8C8F92FFFFF3D5FFDCA251FFDBA4
      54FFF5CD91FFF5CE91FFDDA658FFDDA554FFF5CA87FFE2E5E9FFE3E2E2FFE3E2
      E1FFE2E1E0FFE3E2E1FFFCFBFBFF8C8C8CFFB16C13FFF1B172FFC7FAFFFFC9F3
      FBFFCDF6FDFFAECACEFF5D5250FFAEC9CEFFCCF6FCFFC8F0F6FFC7EEF4FFC8F1
      F9FFC7F9FFFFF1B172FFB16C13FF00000000B47D1DFFFFFFFFFFF3ECD9FFF3EC
      D9FFF3ECDAFFF3ECD9FFF3ECD9FFF3ECD8FFFFFFFFFFAE730DFFEFE4C7FFFFFF
      FFFFCFAB6CFFAC6F04FFFFFFFFFFB58021FF000000004B351FACC9A989FFFFFF
      FCFFB48D61FFA57341FFBE9A73FFFFFFFFFFFFFFFFFFA57340FFA97948FFA776
      43FFB58D62FFFFFFFCFFC9A989FF5E4327C18D8F91FFFFFFEDFFFFF1CFFFF5D4
      A7FFF8DBB2FFFFF0CFFFFFF1D1FFF5D5A8FFF9DBAEFFF4F5F8FFF4F4F4FFF5F3
      F2FFF4F3F2FFF5F4F3FFFFFFFFFF8E8E8EFFA66613F8EBAD6CFFC8E9EBFFC4F4
      FFFFA9C8CCFF605551FFABC9CDFFC8F4FCFFC4EFF6FFC2ECF3FFC2ECF4FFC0EF
      F9FFC7E8EAFFEBAD6CFFA66613F800000000B47D1DFFFFFFFFFFF1E8CFFFF1E8
      D0FFF1E8D0FFF0E7CFFFF0E6CDFFF0E7CDFFFFFFFFFFAE730DFFEBDEBCFFFFFF
      FFFFAC6F04FFFFFFFFFFECDCC4FF523B11AC000000000000000047321CA7C9AA
      8BFFFFFFFFFFB68C61FFA3713CFFA26F3AFFA26F3AFFA67542FFA67542FFB78D
      62FFFFFFFFFFC9AA8BFF47321CA700000000808181EF8D8F91FF8C8E92FF8C8F
      93FF8C8F93FF8B8E92FF8B8E92FF8C8F93FF8C8E92FF8C8D8EFF8C8C8DFF8C8C
      8CFF8C8C8CFF8C8C8CFF8E8E8EFF808080EF3C250895D4934AFFE4CDA9FFBBF5
      FFFF5C514EFF95A8ADFFC2F2FAFFBEECF4FFBCEAF2FFBCE9F2FFBAEAF4FFB7EF
      FEFFE4CBA8FFD4934AFF3C25089500000000B47D1DFFFFFFFFFFEDE3C7FFEDE3
      C8FFEDE3C7FFF6F0E1FFFFFFFFFFFFFFFFFFFFFFFFFFB07510FFFFFFFFFFFFFF
      FFFFFFFFFFFFECDCC4FF4D360EA7000000000000000000000000000000004732
      1CA7CAAB8CFFFFFFFFFFB58C60FFBA946AFFFFFFFEFFA3703CFFB68E62FFFFFF
      FFFFCAAB8CFF47321CA700000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B06A11FFEEB374FFD9DA
      C7FFB6F3FFFFB8EFFCFFB8ECF7FFB8EBF6FFB7EAF4FFB4E9F5FFB2ECFCFFD7D7
      C3FFEEB273FFB06A11FF0000000000000000B47D1DFFFFFFFFFFEBDDBCFFEBDD
      BDFFEBDCBBFFFFFFFFFFCFAB6CFFAC6F04FFFFFFFFFFB37C1BFFB58020FFB57E
      1FFFB58021FF523B11AC00000000000000000000000000000000000000000000
      000047321CA7CAAC8EFFFFFFFFFFB38A5EFFA06B35FFB48B5FFFFFFFFFFFCAAC
      8EFF47321CA70000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000D080146B56F18FFF1B6
      7AFFE6D3B2FFBCE5E9FFADECFFFF62808BFFADECFEFFBCE4E8FFE5D2B1FFF1B6
      79FFB56F18FF0D0801460000000000000000B57E1EFFFFFFFFFFE7D8B1FFE7D8
      B1FFE7D7B0FFFFFFFFFFAC6F04FFFFFFFFFFECDCC3FF4A350FA4000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000046321CA7CBAD8EFFFFFFFFFFC6A886FFFFFFFFFFCBAD8FFF4632
      1CA7000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000D080146B069
      10FFD99C54FFFAC18AFFFFCE9AFFFFCF9AFFFFCE9AFFFAC18AFFD99C54FFB069
      10FF0D080146000000000000000000000000B68123FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFECDCC4FF4D360EA700000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000046321CA7CBAE91FFFFFFFFFFCBAE91FF46321CA70000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00003C250795A46511F7B06A10FFB06910FFB06A10FFA46511F73C2507950000
      000000000000000000000000000000000000A27627EFB68123FFB57E1EFFB47D
      1DFFB47D1DFFB47E1EFFB58021FF805A1BD50000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000004B351FACA67440FF4B351FAC000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000330000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000330000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000002400000033000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000003300000033000000240000000000000000000000000000
      00000000001E00000031000000330000003300000033000000310000001E0000
      0000000000000000000000000000000000000000000000000000000000000000
      003333ABF0FF00000033000000000000000000000000000000000000002D0000
      00330000002D0000000000000000000000330000000000000000000000000000
      0033008B4AFF00000033000000000000000000000000000000000000002D0000
      00330000002D0000000000000000000000335F4105C1B77E0EFFB67C09FFB67B
      08FFB67B08FFB67B08FFB67B08FFB67B08FFB67B08FFB67B08FFB67B08FFB67B
      08FFB67B08FFB67C09FFB77E0EFF5F4105C100000000000000000000000E0000
      0033473117AAAC7637F9B47B37FFB47B36FFB47B37FFAC7637F9473117AA0000
      00330000000E00000000000000000000000000000000000000000000003332A7
      EDFF46E7FFFF33ACF2FF00000033000000000000000000000000090808E60A09
      09FF090808E60000000000000000090808FF0000000000000000000000330087
      45FF00E9A8FF008745FF00000033000000000000000000000000090808E60A09
      09FF090808E60000000000000000090808FFB77E0EFFFDFFFFFFE7E7E6FFE7E7
      E6FFE7E7E6FFE7E7E6FFE7E7E6FFE7E7E6FFE7E7E6FFE7E7E6FFE7E7E6FFE7E7
      E6FFE7E7E6FFE7E7E6FFFDFFFFFFB77E0EFF000000000000000E150F076BB47B
      37FFDEC095FFFDF2DBFFFFFFF1FFFFFFF0FFFFFFF1FFFDF2DBFFDEC095FFB47B
      37FF150F076B0000000E0000000000000000000000000000003331A4EBFF43E2
      FFFF42DFFFFF43E1FFFF35AFF6FF0000003300000000000000001E1C1CFF0000
      00001E1E1EFF00000000000000331D1D1DFF0000000000000033008745FF00E0
      A3FF00DC9FFF00E0A3FF008745FF0000003300000000000000001E1D1EFF0000
      00001E1E1EFF00000000000000331D1D1DFFB67C09FFDCE2EBFFD0D0D0FFD0D0
      D0FFD0D0D0FFD0D0D0FFD0D0D0FFD0D0D0FFD0D0D0FFD0D0D0FFD0D0D0FFD0D0
      D0FFD0D0D0FFD0D0D0FFDCE2EBFFB67C09FF00000000150F076BB98442FFF8EA
      D1FFFFFEEBFFFFF9E2FFFFF8E1FFFFF7E1FFFFF7E0FFFFF9E2FFFFFEEBFFF8EA
      D1FFB98442FF150F076B00000000000000000000003333A4EAFF41E3FFFF3FDC
      FFFF3FDAFFFF3FDCFFFF41E1FFFF36B6FCFF0000003300000000302D2CFF0000
      0033302F2FFF000000002E2D2DFF303030FF00000033008B4AFF00E2A9FF00D9
      9FFF00D69CFF00D99FFF00E2A9FF008D4BFF0000003300000000312D2EFF0000
      0033302F2FFF000000002E2D2DFF313030FFB57A08FFFFFFFFFF767373FF7673
      73FF767373FF767373FF767373FF767373FF767373FF767373FF767373FF7673
      73FF767373FF767373FFFFFFFFFFB57A08FF0000001EB47B37FFF8EAD2FFFFF9
      E5FFFFF3DAFFFFF4DBFFFFF7DFFFFCEFD4FFFFF5DCFFFFF3D9FFFFF3D9FFFFF9
      E5FFF8EAD2FFB47B37FF0000001E0000000032A5E9FF33A5EAFF31A4EBFF46DD
      FFFF3DD9FFFF46DCFFFF34ADF4FF36B5FBFF37C6FFFF00000000343130DD4644
      44FF403E3EF30000000000000000484646FF008F4EFF008C4BFF008543FF09D8
      A4FF00D39BFF09D8A4FF008543FF008E4BFF009850FF00000000353132DD4644
      44FF403E3EF30000000000000000484646FFB47906FFFFFFFFFF6C6B69FF6C6A
      69FF6C6B69FF6D6B6AFF6D6B6AFF6D6B6AFF6D6B6AFF6D6B6AFF6D6B6AFF6D6B
      6AFF6D6B6AFF6D6B6AFFFFFFFFFFB47906FF463217A9DEC098FFFFFBEAFFFDEF
      D3FFFDEED2FFFFF3D9FFCEA46EFFAD702AFFFFF8E0FFFEF1D6FFFDEED2FFFDEF
      D3FFFFFBEAFFDEC098FF463217A900000000000000000000000031A5EBFF4EDE
      FFFF3AD7FFFF4DDDFFFF34AEF5FF000000000000000000000000000000000000
      0033000000000000002C000000330706065A0000000000000000008745FF14D9
      AAFF00CF9BFF14D9AAFF008745FF000000000000000000000000000000000000
      0033000000000000002C000000330000002DB47906FFFFFFFFFF636060FF5F5C
      5CFF615E5EFF656162FF666363FF666363FF666363FF666363FF666363FF6663
      63FF666363FF666363FFFFFFFFFFB47906FFAC7637F9FEF2E1FFFEEFD4FFFBEA
      CBFFFCECCDFFFFF3D6FFAF7531FFF5CB89FFAE732FFFFFF5DAFFFEEED0FFFCEB
      CCFFFEEFD4FFFEF2E1FFAC7637F900000000000000000000000030A5EBFF55DE
      FFFF36D4FFFF55DEFFFF34AFF5FF000000000000000000000000000000000403
      03FF00000000070707E3070606FF050404E30000000000000000008845FF20D9
      AFFF00CC9AFF20D9AFFF008845FF000000000000000000000000000000000403
      03FF00000000080707E4080707FF060505E5B47907FFFFFFFFFF565453FFFFFF
      FFFF504E4DFF595756FF5D5C5AFF5E5C5BFF5E5C5BFF5E5C5BFF5E5C5BFF5E5C
      5BFF5E5C5BFF5E5C5BFFFFFFFFFFB47907FFB47B36FFFFFFFBFFFBE7C6FFFAE6
      C6FFFBE8C8FFFFEFD3FFB17835FFE2AF61FFE7BA76FFAF7531FFFFF0D4FFFCE9
      C9FFFBE7C6FFFFFFFBFFB47B36FF00000000000000000000000030A5EBFF5CDF
      FFFF33D2FFFF5CDEFFFF33B0F6FF000000000000000000000000000000331C1C
      1CFF000000001E1E1EFF000000001D1D1DFF0000000000000000008845FF2ED9
      B5FF00C99AFF2ED9B5FF008945FF000000000000000000000000000000331C1C
      1CFF000000001E1E1EFF000000001D1E1EFFB47A07FFFFFFFFFF4F4C4CFF4340
      40FFFFFFFFFF4F4C4CFF565353FF575454FF575454FF575454FF575454FF5754
      54FF575454FF575454FFFFFFFFFFB47A07FFB47B36FFFFFFFCFFFAE2BEFFF9E2
      BFFFFAE4C2FFFFEBCDFFB27937FFD29E4EFFD19C4CFFD09A48FFAD712CFFFCE6
      C6FFFAE2BFFFFFFFFCFFB47B36FF0000000000000000000000002FA5EBFF65DF
      FFFF2FD0FFFF65DEFFFF33B0F7FF0000000000000000000000002E2C2CFF3130
      30FF00000000302F2FFF00000033302F2FFF0000000000000000008844FF3BD9
      BBFF00C69AFF3BD9BBFF008945FF0000000000000000000000002F2D2DFF3130
      30FF00000000302F2FFF00000033302F2FFFB47A07FFFFFFFFFF474545FFFFFF
      FFFF413F3FFF4A4848FF4E4C4CFF4F4D4DFF4F4D4DFF4F4D4DFF4F4D4DFF4F4D
      4DFF4F4D4DFF4F4D4DFFFFFFFFFFB47A07FFB47B36FFFFFFFFFFF7DFB8FFF7DF
      B9FFF8E1BCFFFDE8C5FFB27937FFC28A37FFDCBE8FFFB07633FFFDE9C7FFF9E1
      BDFFF8DFB8FFFFFFFFFFB47B36FF0000000000000000000000002EA5EBFF6DE0
      FFFF2DCEFFFF6DDFFFFF32B0F6FF000000000000000000000000000000004A47
      47FF000000003F3D3DF2464444FF353333DF0000000000000000008844FF47D9
      C0FF00C299FF47D9C0FF008944FF000000000000000000000000000000004A47
      47FF000000003F3D3DF2464444FF353333DFB47A07FFFFFFFFFF424040FF3E3C
      3CFF413F3FFF454343FF464444FF464444FF464444FF464444FF464444FF4644
      44FF464444FF464444FFFFFFFFFFB47A07FFAA7736F8FEF4E8FFFAE2BFFFF6DA
      B2FFF7DCB5FFFBE2BDFFB17834FFE4D0B0FFB07632FFFCE4C1FFF8DEB8FFF6DB
      B3FFFAE2BFFFFEF4E8FFAA7736F80000000000000000000000002EA5EBFF76E1
      FFFF29CBFFFF76E0FFFF31B0F6FF0000000000000000000000000000002D0000
      00330000002D0000000000000000000000330000000000000000008843FF53DB
      C4FF00BF98FF53DBC4FF008944FF0000000000000000000000000000002D0000
      00330000002D000000000000000000000033B57B09FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFB57B09FF3E2B1495DEC19EFFFFF5E8FFF5D7
      ABFFF5D8AEFFF8DDB5FFCC9E64FFAF7530FFFBE1BAFFF7DBB3FFF5D8AEFFF5D7
      ACFFFFF5E8FFDEC19EFF3E2B14950000000000000000000000002DA5EBFF80E3
      FFFF25C9FFFF7EE2FFFF31B1F8FF000000000000000000000000080606E60706
      06FF070606E50000000000000000040303FF0000000000000000008843FF60DC
      C9FF00BC98FF60DCC9FF008A44FF000000000000000000000000080707E60706
      06FF070606E50000000000000000040303FFB57D0EFFF8E1C0FFDEA951FFE1AF
      5FFFE3B366FFE4B66BFFE6BA72FFE8BD79FFEBC183FFE8BC75FFE8BC74FFE8BC
      74FFEABD70FFEDBE6DFFFEECCFFFB67D0DFF00000000B57C37FFF8ECE0FFFEEB
      D4FFF4D2A4FFF5D4A9FFF7D7ADFFF7D8AEFFF6D6ABFFF4D3A7FFF4D2A4FFFEEB
      D4FFF8ECE0FFB57C37FF000000000000000000000000000000002DA5EBFF88E3
      FFFF22C6FFFF88E2FFFF31B1F9FF0000000000000000000000001E1E1EFF0000
      00001D1E1EFF00000000000000331C1C1CFF0000000000000000008843FF6CDC
      CEFF00B898FF6CDCCEFF008A44FF0000000000000000000000001E1E1EFF0000
      00001E1E1EFF00000000000000331C1C1CFFB78113FFF3DAB1FFC57300FFCA81
      00FFD18B14FFD59428FFDB9E3AFFE0A94EFFE8B465FFB17601FFF0D5A8FFB276
      00FFF4D7A1FF1F2EECFFF7DBA7FFB88111FF000000000D090446B98542FFF8EC
      E3FFFFF3E6FFF7D9B2FFF3CF9FFFF3CF9FFFF3CF9FFFF6D9B1FFFFF3E6FFF8EC
      E3FFB98542FF0D090446000000000000000000000000000000002CA5EBFF91E6
      FFFF1FC5FFFF90E4FFFF30B1F8FF000000000000000000000000302F2FFF0000
      0033302F2FFF000000002C2B2BFF302F2FFF0000000000000000008842FF78DF
      D4FF00B597FF78DFD4FF008A43FF000000000000000000000000302F2FFF0000
      0033302F2FFF000000002E2D2DFF302F2FFF523A0BABD9B46BFFEDD09CFFECCF
      9CFFECCF9BFFECCE99FFEBCD98FFEBCD97FFEBCD97FFECCD97FFECCD96FFECCD
      95FFEECE92FFF2D191FFDCB466FF51390AAA00000000000000000D090446B57C
      37FFDFC1A1FFFFF4F0FFFFFFFFFFFFFFFFFFFFFFFFFFFFF4F0FFDFC1A1FFB57C
      37FF0D09044600000000000000000000000000000000000000002CA5EBFF9AE7
      FFFF1CC2FFFF9AE6FFFF2FB1F8FF000000000000000000000000353333E04543
      43FF3D3C3CF40000000003030337454343FF0000000000000000008842FF86E0
      D9FF00B197FF86E0D9FF008943FF000000000000000000000000353333E04543
      43FF3F3D3DF50000000000000000474444FF000000009B6E15EAB78216FFB782
      15FFB78115FFB78115FFB68114FFB68114FFB78114FFB78114FFB78114FFB781
      14FFB78113FFB88214FF9C6E14EA000000000000000000000000000000000000
      00003E2B1495A97535F7B47B36FFB47B36FFB47B36FFA97535F73E2B14950000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000001E00000031000000330000003300000033000000310000001E0000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000001E00000031000000330000003300000033000000310000001E0000
      0000000000000000000000000000000000000000002300000033000000330000
      0033000000330000003300000023000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000002B0000003300000033000000330000003300000033000000330000
      00220000000000000000000000000000000000000000000000000000000E0000
      0033333130AA797472F9817978FF817978FF817978FF797472F9333130AA0000
      00330000000E00000000000000000000000000000000000000000000000E0000
      003311174BAA2938B5F92A3ABEFF2A39BEFF2A3ABEFF2938B5F911174BAA0000
      00330000000E00000000000000000000000060564EC0B7A596FFB6A394FFB6A3
      94FFB6A394FFB7A596FF60564EC0000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000317794E1399BC3FF3699C2FF3699C1FF3699C1FF3699C2FF379BC3FF194A
      5FB900000033000000330000003300000023000000000000000E0F0F0F6B847C
      7BFFC5B8BAFFF9E8ECFFFFF7FDFFFFF7FCFFFFF7FDFFF9E8ECFFC5B8BAFF847C
      7BFF0F0F0F6B0000000E0000000000000000000000000000000E0507166B2A3A
      BEFF495AE2FF6073FBFF677AFFFF6679FFFF677AFFFF6073FBFF495AE2FF2A3A
      BEFF0507166B0000000E0000000000000000B7A495FFE4D8CBFFE1D5C8FFE0D4
      C7FFE1D5C8FFE4D8CBFFB8A596FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000230000
      0033399BC3FFEFFFFFFFDEFBFFFFDEFBFFFFDEFBFFFFDEFBFFFFEDFFFFFF2B97
      C3FFBAB1ABFFB0AFABFFAFAFADFF5C5C5BC0000000000F0F0F6B8F8786FFE8D8
      DBFFA9E5D3FF17DDA3FF00D991FF00D992FF00D992FF1ADEA4FFAAE6D3FFE9D8
      DBFF8F8786FF0F0F0F6B0000000000000000000000000507166B2E3EC2FF586C
      F6FF6074FFFF5A6FFEFF5267FDFF4E64FDFF5267FDFF5A6FFEFF6074FFFF586C
      F6FF2E3EC2FF0507166B0000000000000000B5A293FFE9E1D7FFF2EAE1FFF1E9
      E0FFF2EAE1FFE9E1D7FFB8A494FF000000000000003300000033000000330000
      0033000000000000003300000033000000330000000000000000215065BE3B9C
      C4FF3397C0FFE6FEFFFFC6F1FDFFC5F1FCFFC5F0FCFFC5F1FDFFE4FDFFFF2491
      BEFFFFFFFFFFFFFFFFFFFFFFFFFFB0B0ADFF0000001E8B8483FFE0CFD2FF6CDB
      BBFF00D690FF00D38EFF00D290FF00D494FF00D696FF00D696FF00D793FF6FDB
      BCFFE0CFD2FF8B8483FF0000001E000000000000001E2B3BBFFF5568F4FF5C70
      FCFF586CFAFF4C62F9FFA4AFF9FFFFFFFFFFA4AFF9FF4C62F9FF586CFAFF5C70
      FCFF5568F4FF2B3BBFFF0000001E00000000B5A191FFF2EDE5FFF8F3EFFFF7F2
      EDFFF8F3EFFFF2EDE5FFB8A393FF00000000737475FFB0B1B1FFAEAEAEFFB1B1
      B1FF00000000777777FFA2A2A2FFAEAEAEFF0000002B000000333A9BC4FFF6FF
      FFFF2C93BEFFE4FDFFFFB8EBFCFFB7EAFBFFB6EBFBFFB7EBFCFFE2FCFFFF238F
      BCFFFFFFFFFFFFFEFDFFFFFFFFFFAEAEABFF373634A9BBAEAFFF99D4C3FF00D1
      91FF00CC8CFFFFFFFFFFFFFFFFFF00CC8DFF00D096FF00D299FF00D298FF00D4
      96FF9CD4C4FFBBAEAFFF373634A90000000011174AA94255DEFF576CFBFF556A
      F8FF5267F7FF445BF6FFFFFFFFFFFFFFFFFFFFFFFFFF445BF6FF5267F7FF556A
      F8FF576CFBFF4255DEFF11174AA900000000B4A091FFFAF9F5FFFFFEFEFFFEFD
      FCFFFFFEFEFFFAF9F5FFB6A292FF000000000000000000000000000000000000
      000000000000000000000000000000000000317795E13B9CC4FF3498C1FFF0FF
      FFFF2991BDFFE4FDFFFFACE8FCFFC0EEFCFFE0FAFFFFE1FBFFFFE4FDFFFF228F
      BCFFFFFFFCFFFBFAF9FFFFFFFFFFADADABFF8B8684F9D3C2C5FF0DCE9DFF00C9
      8CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00C98DFF00CD96FF00CF99FF00D0
      98FF16D0A0FFD5C2C5FF8B8684F9000000002A3AB5F94E63F4FF5067F7FF4F65
      F5FF4D63F5FF4159F4FFA4AFF9FFFFFFFFFFA4AFF9FF4159F4FF4D63F5FF4F65
      F5FF5067F7FF4E63F4FF2A3AB5F900000000B5A292FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFB6A393FF000000000000000000000000000000000000
      0000000000000000000000000000000000003B9CC4FFF7FFFFFF2E94BFFFEEFF
      FFFF2991BDFFE5FDFFFF9EE4FCFFE1FAFFFF6CB7D5FF238DBAFFE6FFFFFF208E
      BCFFFFFBF8FFF9F7F6FFFFFFFFFFADADABFF948E8DFFD4C0C3FF00C98FFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00C48DFF00C995FF00CB
      98FF00CD97FFD6C0C4FF948E8DFF000000002C3BBFFF4D64F8FF4B61F4FF4B61
      F3FF4A60F3FF445BF3FF364FF2FF2F48F1FF364FF2FF445BF3FF4A60F3FF4B61
      F3FF4B61F4FF4D64F8FF2C3BBFFF000000009D8E81ECB5A292FFB4A08FFFB39F
      8FFFB4A08FFFB5A292FF9D8E81EC000000000000000000000000000000000000
      000000000000000000000000000000000000379AC3FFF1FFFFFF2B93BEFFEDFF
      FFFF2991BDFFE6FDFFFF91E0FCFFE2FBFFFF238EBAFFC6F4FFFFE2FDFFFF72B5
      D1FFFCF6F4FFF5F2F2FFFFFFFFFFADADABFF989291FFD0BABCFF00C691FFFFFF
      FFFFFFFFFFFF00C08BFF00BF8BFFFFFFFFFFFFFFFFFFFFFFFFFF00C18EFF00C6
      96FF00CA97FFD2BBBDFF989291FF000000002B3ABFFF5E73F7FF445CF2FF465D
      F1FF455CF1FF3F57F1FF6E81F3FFFFFFFFFF6E81F3FF3F57F1FF455CF1FF465D
      F1FF445CF2FF5E73F7FF2B3ABFFF000000000000002300000033000000330000
      0033000000330000003300000023000000000000000000000000000000000000
      000000000000000000000000000000000000379AC2FFF0FFFFFF2B92BEFFEDFF
      FFFF2B92BDFFEAFFFFFFE5FDFFFFE6FEFFFFE8FFFFFFE4FFFFFF6FB3CFFFFBF5
      F1FFF3F1EFFFF0F0EFFFFFFFFFFFADADABFF999392FFDCC6C9FF00C394FF00C0
      93FF00C093FF00C196FF00C196FF00BC8EFFFFFFFFFFFFFFFFFFFFFFFFFF00BC
      8DFF00C293FFDCC6C9FF999392FF000000002939BFFF6F84F7FF3E57EFFF405A
      EFFF3F58EFFF3650EEFFA3AFF7FFFFFFFFFFA3AFF7FF3650EEFF3F58EFFF405A
      EFFF3E57EFFF6F84F7FF2939BFFF000000005C534BBDB7A596FFB6A495FFB6A4
      95FFB6A495FFB7A596FF5C534CBD000000000000000000000000000000000000
      000000000000000000000000000000000000379AC2FFF0FFFFFF2B92BEFFE0FB
      FFFF45A8CEFF2A92BDFF2991BDFF2992BEFF2892BEFF4AA2C6FFECEBEBFFF1EE
      ECFFEEECEAFFEDEBEAFFFFFFFFFFADADABFF938E8CF8DECDCEFF15C3A1FF00BF
      98FF00C099FF00C19AFF00C19AFF00BE97FF00B98EFFFFFFFFFFFFFFFFFFFFFF
      FFFF03BE9AFFDCCCCCFF938E8CF8000000002736B5F893A1F4FF3650EEFF3A54
      EDFF3A54EDFF2D48EBFFDADFFBFFFFFFFFFFDADFFBFF2D48EBFF3A54EDFF3A54
      EDFF3650EEFF93A1F4FF2736B5F800000000B7A595FFE4D9CDFFE2D8CCFFE3D9
      CEFFE2D8CCFFE4D9CDFFB8A596FF000000000000000000000000000000000000
      000000000000000000000000000000000000379AC2FFEFFFFFFF2A92BDFFEDFF
      FFFFECFFFFFFEDFFFFFFEDFFFFFFEAFFFFFF74B5D0FFF9F0ECFFFAF5F5FFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFAEAEABFF36343395C7BCBDFFA1D5CAFF00BC
      95FF00BD99FF00BE9AFF00BE9BFF00BE9AFF00BB96FF00B68EFFFFFFFFFFFFFF
      FFFF8ED0C3FFC4BBBCFF36343395000000000E134195838EE2FF697EF2FF304C
      EAFF324DE9FF2541E8FFFFFFFFFFFFFFFFFFFFFFFFFF2541E8FF324DE9FF304C
      EAFF697EF2FF838EE2FF0E13419500000000B6A394FFEBE4DCFFF7F3EFFFB06F
      21FFF7F4F0FFECE6DFFFB8A596FF000000000000003300000033000000330000
      0033000000000000003300000033000000333799C2FFEEFFFFFF53B2D6FF2A92
      BDFF2B92BEFF2B93BEFF2993BFFF73B3CFFFF5EDE9FFEBE9E7FFFFFFFFFFCBCB
      CAFFA6A6A4FFA5A5A2FFFFFFFFFFAFAFADFF00000000A19B99FFEDDCDEFF73D1
      C2FF00B696FF00B899FF00B89AFF00B99AFF00B899FF00B595FF00B18EFF60CC
      BBFFE5DADBFFA09A99FF0000000000000000000000002E3EC2FFADB7F5FF6579
      F0FF2744E7FF1E3CE6FFBCC4FBFFFFFFFFFFBCC4FBFF1E3CE6FF2744E7FF6579
      F0FFADB7F5FF2E3EC2FF0000000000000000B5A293FFF4F1ECFFAD6B1BFFFEFF
      FFFFAE6E20FFE6D7C1FFBAA899FF00000000737475FFB0B1B1FFAEAEAEFFB1B1
      B1FF00000000777777FFA2A2A2FFAEAEAEFF3A9BC3FFF1FFFFFFEEFFFFFFEFFF
      FFFFEDFFFFFFECFFFFFF65ADCBFFF4EAE6FFEAE6E4FFE5E3E2FFFFFFFFFFA6A6
      A4FFFBFBFAFFFFFFFFFFE9E9E9FF4F4F4EAC000000001414145BAAA2A0FFF5E5
      E7FFAFE2DAFF19BEA6FF00B194FF00B294FF00B194FF18BEA6FFADE1D9FFF2E5
      E6FFA8A2A0FF0C0C0C4600000000000000000000000003040E463E4DC8FFA0AC
      F1FF8D9CF4FF4961EAFF1C39E5FF1130E3FF1C39E5FF4961EAFF8D9CF4FFA0AC
      F1FF3E4DC8FF03040E460000000000000000B4A191FFFCFBF9FFFFFFFFFFFFFF
      FFFFFFFFFFFFB27122FFB9A799FF000000000000000000000000000000000000
      0000000000000000000000000000000000001E4B5EB03A9BC3FF3699C2FF3398
      C2FF2A95C1FF4FA9CDFFE1E0DFFFE6E2DFFFE1E0DFFFE0DFDEFFFFFFFFFFA5A5
      A2FFFFFFFFFFE7E7E8FF4B4B49A70000000000000000000000001514145BA59F
      9DFFD9CFCFFFFFF4F6FFFFFFFFFFFFFFFFFFFFFFFFFFFFF4F6FFD9CFCFFFA59F
      9DFF0C0C0C46000000000000000000000000000000000000000003040E462E3F
      C2FF6976DCFF9EAAF2FFADB9F8FFADB8F8FFADB9F8FF9EAAF2FF6976DCFF2E3F
      C2FF03040E46000000000000000000000000B5A292FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFB7A596FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C0B3ABFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFE9E9E9FF4A4A49A700000000000000000000000000000000000000000000
      0000393737959E9897F7A8A2A0FFA8A1A0FFA8A2A0FF9E9897F7393737950000
      0000000000000000000000000000000000000000000000000000000000000000
      00000E1341952534B4F72636BFFF2636BFFF2636BFFF2534B4F70E1341950000
      000000000000000000000000000000000000A19284EFB5A292FFB4A08FFFB39F
      8FFFB4A090FFB5A393FFA19285EF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000565452AFB2B0ADFFAFAEACFFAEAEABFFAEAEABFFADAEABFFAEAEABFFAFAF
      ADFF4F4F4EAC000000000000000000000000424D3E000000000000003E000000
      2800000040000000400000000100010000000000000200000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000}
  end
  object icToolbar: TImageCollection
    Images = <
      item
        Name = 'asterisk_orange'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000008284944415478DACC577B7054D519FFDDBD7BF79DCDEE26
              BB9B171B24098487A4806520C850B576D48E1DC5696B9D42AD0F8ADA693B5619
              EB68B53E0023C260751C19A9532533E954A6B54CB5033540A5038C440D026120
              E4B1C96E36D96477B38FECE3EEBDA7DFD9BDD0140884FEE599F9F6EC9EF3FB1E
              E79CDFF79DB302630C5FF7A63BF1A2F77EFF964A76F2E5AAF5FCF754383ECF71
              1C7F05DCF41D7FF582E727BD1B9D1391DDF7B2CCD1D758DF2B9E1C8D5BA6C09B
              CF6DF684388EE3B91ED7FF7F02D19DDA58BD9E9C6523BB7FC858EF478C05DA19
              0B1E6081371A59DBFAB29B09235CA423FCF9D1F29B03BF9FC358B8A388273DAE
              CFED707B530572C9E0F797DAEC1683D0E25CB8DAE06C7E0CE8DF03FC7D3530D8
              0EE7A2355858A3FB1DC1A48BD4A4395EE197CEC56B809E0F097F77418FEB733B
              64EF55C218A7BB03250BAA0DCBFB5FAD64F2BB3EC6769615E5FD7AC606F632FF
              561F5BBBC25A315961FD4DB60A3ECEE7595B1363EF1475B83EB7C3ED71BBD3DA
              016AD913815CA0F568F689508C32C460A6F599C0E418307E0625F5ABF0F877AC
              9B08276A78F1A19596274BEA5615E6D9C420E9980A7A5C9FDBE1F6B8DDE906C0
              89167EFA83C8DF3AFAE45DC351F2A33740D0D30EF6ED81A3F176388C2A67B9F9
              3CF9CA2DEAE38EC6DB80E027843315F05CEFF490B287DBE1F634BBD30A80B70C
              C9F05DDB432DE1B8DA134FF1533600914EA25B1E36DF22B46F70DF47A3FA834F
              B9EFB3562F224B0A103A5CC0713CD7BBB525F82C6146347BB896007875E26E87
              AE7F66E047D1B88A4C8E886FA05D08FC03F6865B30D3256CA5797BB51DCF9436
              52620C7F5A98CFE50544C755901E0F304892D4EC5D5300BCD192304E32F8E87B
              E17BC26379A89CFCE163905CD530D91CD68F7F55F60B53897386E469A0500F10
              1B68EBC3796CDB1B7B90EB91C4343BB8620003DB6AC529E66592B18F3A273E3F
              783AB37D384C3F455A4CB4138E79B7A1D1A33E57DA40E40B1F298C0F0DE5F079
              5FEE8FDBF78E1FE47A9AFE256D609BEF823F3D67712697DFD1DFE27D80DF0B8A
              2A74AA0C671408DDB282430CBAC8C2678327D7EC18797BDF1315B30C12EE2C33
              B6C3DCF03044A30DB69974FE7DAD888EC9E809653FBDEBF5D0164EBACE17AA9A
              74022B9344DC2882D5D3F7D9A28E350982807456FE0361D6F1DDE115CD46CE13
              BE1F6C26AA24214783C8A763905311E4A221C8E928F5435098104BE7306C3560
              8EBBC200EBA2B584C942B21A913EBE0BA14006A91CCE580C708B02731A9C95D0
              51E6983D75D49B60745611B694AA811B23ED3BE07DE008AF0B49BE03A6E28D48
              32B01B92E4A4B477C0ECA8057C74B6D61985C2ABA6A20E6522EAC84402907329
              28B16E4815CD50820790B52C806B9E1535DEBAD9A2C5019DD559A45D861240A1
              EC4B111DE41ECA921005F053B0643FDF7DD3F90074050F137EA8594AD76CA458
              E9D9F9646010241B49092463391190D2D14881093AB07410A2AB110E17E13264
              5CF5838D76800D25A87025FF7B65D0B617ED29D0A57AC9A378817FFA2280BE67
              868AC546100B7A42F14333A040C98C224FC7934DA621397D30D7DD4A194E5CF3
              AC42B6FF9FC886FB61B499A1371B2819F464D27221A159F183841222439929E8
              319984142039CDD184A8873C91879C5590CFE5919BC869BD8CB4CC6292A01ACD
              A50E73E5926F53827660F47417DC921106DF2D18ED6D4578309296A1CB9825C1
              69B0485410F5A09BA8D04B46119285DCE568A1A2F83F01A8FD11750F0E7D7127
              8F3292623DB1B41A884E28814EBF7C6224A1C4DE6A8F9F2EB3E98CC79EABF9AB
              67E91D10B2BDB4E273484665944606A8EC7B50D5FC5D0C7EF227F3C33BC30FED
              EFCA0C3F72937D8EC72E3A9B7CD202A745AC769875D52EAB308BD7A6B323F936
              EE17DA21D9488869706B174C769264B41ACE7A367BBBAA96DF6135BA88C991A3
              18EB89E2ECD9F1E3D7F92C0BBD73BD806B2972F124860EED41F3A6D1FA604CE1
              35C0A091CD384914AD3CF342951434A7660D286880FCA45EE8DE5471CC3D77C9
              7C7BC302B0B1C350F30A068FF563E686C1DBFB5A6A3E9E71432D1DAB08A16C39
              127D5D18FDEAB3E0ACA786EAB555EA351FE77BA62D2CCD7DE834479CB2A3DAAD
              456980B87617E44FBC58F14649956FBE7DDE62B0F12FC9910EF1A1711C0FC8EF
              F2BB82F7517FA430CEE74B1A9A609F515B75EAA5CA566D0129CD5E44B33FAAF9
              53AE7617E83EFB6DE5FD2EB7F341CF375782C5BB0AA7C26811A9501CBFF920FA
              160FE07BDB87B7A6C75285F1C23CE15CDF58014799E3EE2F9EAFFCF5D5DE8453
              4D0A6D8FB81B2A4AA577CA17AFA09C8E52218914D234313C8E8131B9FD6480A7
              4DE1B289D0EFFDF140B430CF0847F90ACFB295282F915ED9F7A477D965DE9057
              0DC0B06CA6FE4B67D30D906C12D40C1529916E42498F847F0C6FEE4FF0375E42
              236862EDCED1A793C168619E114ECD06E89E10E15E7E236697EBFEFDD26AA7EB
              5A02907A5A6A4EDBEBEA4CD659B564CC4FD491A89EEB69EBA3888D67BB5B0F27
              BB3412F196EE1E9603347E8ECF731C743AD21B84D1EB4169E35CFCB8D9D6A365
              C4D50358D35CE20CC5D583893E3F22470E425554E84CF4242389F78D60DFA9CC
              EB1AA9F29A0AEF13EF1D4E3DCFE7398EE355254FD9FA2F8C9FEDC64044F950CB
              B24BCFFA3263BC2E549354EE7ECCFDB3253EE95E9BCF038BC789E18EB3F2751B
              06E7F32BFDA26716CFEF9ADE969A2EEF92066962248AA47F041D7EB9ED9E37C3
              6F73B26A799F9ACEB35CD482A824B99EE45B7FF9B9A7CDBF65067B7F9D6723FD
              F65CEE8F092F64BBD6795EE6388EE77A9A7EA5664F9CEE0E4C0E846F9B9DA45C
              2B5611ED9D3771193CBF7DAA485C1A3F46B5A3CA5CE959264C73474CDABFA19C
              66509D824F268D6CF2D51C7F6DDA7F041800368AA06DF4CBD8C5000000004945
              4E44AE426082}
          end>
      end
      item
        Name = 'folder'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000003E04944415478DAEC57CD6F13471C7D33BBB65312899A96
              0F21942FA92024242A622AF5542195AA155505774455A987568453FF819EB8E4
              8090A8CAA98756AD440B1254702C7080B62A1F6DF908D034C5761D43889338B6
              93C6F6EE4EDFEC6EEC756C27A45A941E187924CF7A35BFF77BEFFD7E33164A29
              ACE69058E5F11C80E0346F9CD873D680B54F390E97AAE56B424AD830CF0F0C5E
              3AC0075658004CCE1774F09D1F7DC16DB9AF126D601AF8FDF30FDED5EF7316C3
              04D0E166CEE0957B4799BFE1470C0E1BB19E43B0CAF3B879FCF582106265344B
              43B37781ECED5FCC9E598BE6585032CA55843310402BA26C38E51C060E7FD38C
              6DD9E8DCC08C90BDF7F7B562CFAC072230C9A5301B19109E57ABB9CBC0C4C5D6
              F2B41BEC3182B947B77E02CF5FE8680F0015262E355F2D76D5CF8D0025F5C842
              8A2530282F3155F2F76D7ED5AC6DE65419C76803A095AE5E65CC4D16B0B4256C
              1899BBD0BEF9F4E0F6FEB7121BBBA3A68C25062FFEA8110618B0DC0DBDD62096
              0D2E0D89E4CD114CA51FB529DD85D4B40CB749A0C47BAFC57F12A8722D71FDC4
              9E0B099A32E001DB63C0A55BD3DABA1CDD5FB859EAC603A05A4662F04BD7C04B
              8168922542539EFCD035655D02557575167A1A8647AB68964D5399FCE53EA5B5
              D1BDB31795074368DFC0160F0746670FB0EE1DE48B956B7C1035835A4932208D
              0892D787917B38E6D2D7AA7BAFEBDE889E57FBE038CA65CDF3975A36716D48D9
              D58FDCE835DCCDCC7EAF83367A80DD6E269B83353F8BDD1F1F23607B1103C205
              60654FC1519EBA904F7B9C382E08B9660B0A7F9FC2E1CFEE7CCB87F3660D3B3D
              200D13D3D909C47B7750913958E3671B4DB920892E492156D893F87E6C13EC8A
              8DA9CCC884DF0F2A7506A4D788F2E9716CDEF526B18D711DF5EB5FACA0FB2C71
              F4766C20FDBF623835FD1597654D8BE963735BE63F3325C4BAA288ADDD0CABF4
              076347433AB13D7FC8D87A14335730747AF46B4D7F63279436727F6548FF3682
              71F82978ADF93F66BB587F1189B35AAB28641F9687D3C5273E033E00E116388A
              8F73E87F23416526BD8E28C2BAAF38CC3E8EA9D43DA42766CFFBD9DB3500BAB6
              D55C9EC76D051D2F6FE2F771C60E2B7BDF33912EFAEB0AAEDECF9F59C8BE8181
              D2A32CD66EE9714F30BAC1A71FA1E82FCC4EB7A48B63490C7D37F2F382FE7506
              58CB93C9145EEA7B85AB59C60E337B8E482766D27FE271BEFC831B207029A949
              904FA6D1FB36DB7399E6D388C31CA47F269DC2AD64E99C9FBD0A16F486DF4EEE
              1D95505D0EAF658E777108F7E6CB0469C3C2C0914BBBB8CC043DA001BCC8D9C7
              190F97F7A64690E74C714E7B7DB90E80974068CEA3CFF82F40C5D7BF8AFFD310
              CFFF9CAE36807F051800FF6F60E9735B68090000000049454E44AE426082}
          end>
      end
      item
        Name = 'disk'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000005B54944415478DAC4575D681D45143E33B37BD3FCD692A6
              3E08A2202AB48242F14121980BFA64513456239A061BC5C6BFAA4F3E08067C11
              A14223F4C1227929B5154BAB20689E941215518BF81404A520DAFCB5699034F7
              EECC78BE33B337F786BBB72415BA61EE6E7677BEF39D6FCE39735679EFE97A1E
              097E945238A5378E7FF957E6A90FA41CF3E26B396F96225035FF242A9C61C778
              7B66767CCF203FCAE4A5A8008CCFBD33BDE47F99B7FEE739EBA7FFC9FCFF7500
              0B98C0868D1D6F9FFE22773E89643BD9DBED4FDDD945BB3EFA9D52A369A56269
              FE853EBA5C71A2C2660E78DD53D274DFC773D45E3254B58E7E7BFE369AF8BAF4
              303F6EE7B1ACE3BB2528B1CA96BADA52F26727A97D4B8912D64E33191989A95D
              2B1975CF9ADC53725682012C60021B36A2EA5BEA159015AB5A4F6D8926C7C600
              60B421BEE4EB9414BBE378A2AF0178D25ACB3CFCDF788F63C73952CEB20A8A4A
              8CE51908D8B011A223FC24F511B39A390E184F1D37EFA42A9F0941C3130F8E3E
              CBDE18EAEFEF1760C7C0832307E8D5E7866860A02CC61BEF0D5096597A7C7894
              21BC60A68C69F80C1BC1745D16E474AA1611EBA8E38E7BE9F22AD8076F0E4F1E
              6705D80B18F72135F03731F9494D018A0A7C3879429E812859C660E512B2D4CD
              98158E01D850D484008E2A03A79236CC5AD4D5923A8ACF5A19727CAD016FFC1A
              488C509324F25E4E46325B5424C102A657C106518102EC3467800A1398B9017B
              5E82B1E1277809125902A8B006C19EB2574FBF7890C69E19AC5B26CBCE5B1A1A
              7D8915F082250EB195D5560A58EFA2619241E211D19163A770C9C6F3BAA16A04
              109490FBC8B1CF1ADEC997408A4F7426B74145042A8801132A57AA4344630D63
              605330CD6046B8B11125CB02837807263C48406B32312B0256AA952C0B6C3427
              80F5B178514BB4263201C60CEDDFFB080D94CB22EBC8CB6FD0E8938F49AE43EE
              2CCB681FDFDBBFF7512A232328A4A4E52C181E7B3D64812C01E3F990EA855980
              DA0FA65A5164AC45E2A327CFC4B22DAAD2D113A7C41BC453549AEF9D967BF9DE
              264ABBA0591A09682690F9ABC50007A1C12456D0E09AC16D5C361537265727A3
              CA23D2356E5AB81F8298A4B443597BB518C890054C8FED52071398FA63851EBC
              B5FD9AF60260002BE558D03ED82824806792053CB19367BCF7FD3CBD3BEDAF89
              00E40796D4131F6C1413706182D121DAB10C52F836D911680A910F2240D06E6D
              390B62201422691EE2FFA85C990B1BD1C6BC57227BAEA88F8A584FC59510EC92
              9805794C0CDDA268E8EE5E09327147C587B5FA5FE83E1D3FB7409F9E8F452D26
              85752DB2C0FB182C2A6FC53C1BEFA35FFF5CE49B09A529F70869989255AB54E5
              E12425D611F10163E89EED74F2FC1C2BA0D6307DCB20F4927AF93EA255C863AD
              53DAD1DB43873F789F7E3C3B2528BBEF2FD36B6FBE45B38BCB5278946A744458
              F860D8C42AA8A28D4202F0580A50942B896B819E606B8FA19FBEFB8676EE7E40
              DE5CB8F42FF574195A58D2D4B46D8DAEE655300F44DF8A80739A5F46ECFA3502
              8862946774AE69CA4BC02D1B0A56920A68E8800A0828B58E80121BC504F80F1B
              07D514A0D81525A20ACE06ED1583608F80ACB847EBAA5BFDFE12B6768A81EDC5
              468B25205180A2026968E6790D35825A8C62786C3049BC87F79B25830FE4D33A
              05A47B6A5588903BA544F653CE578E07179ACE347413D2704845D3417A608248
              D87E1B8DABB879CB3E803DA596C2054BC01DEC25EE7E6EE86E8B0D455EBAD0B3
              A76109ACCD28AB54427563D90155E22568560E72339DDC8A77A7BAF665840ECB
              2F2F7C9B074E4EA072617CCF4387FCE753DE245B4355F4B4CC1F25FBB6DD4ECB
              5547334CA1675BEFD895958BCA66555AECBB6BD70FE7660E64B679A106810BFC
              5132F1D50C7597745000569766A7E70E8DBCC29757C2AE2939AC52BEEEE37113
              8F6E6A2C56F9B1C263219E91145D3C40B66D03151ADF831779FC1DCF594E40BE
              0FA118542D985C8DC6B348B014BF6ECC0608F8E8F9CAFA8FD3EB76FC27C000F3
              45D86935144A730000000049454E44AE426082}
          end>
      end
      item
        Name = 'arrow_undo'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000005CD4944415478DAC4576B4C145714FEE6B1EC2EEC022268
              A0B23C8A60D092D636D580E2037CE0A38DD51F4D7F1862FBC7FE6B342DA68DB6
              4951B1696D52E31FA3A94D497C44C5D0D61A255A8BA8F8C0378AC0C65D565844
              845DD8E7CC4ECFCCCE22E8B2AC8DC4CD9EB993997BCFF9CEB9DF39F70C234912
              5EE78F972F0CC38C7856B60335A284E5A28C2D0A7CA129B21AFA77B0124EF4B5
              6363E31E38C65ACBC811780E807171151CFBCBF7A2D757A3626422981611C7AE
              5446594DB3FD0E9A2C5771BEB5015E2F8E0C74E0B30BBBD1F73200524AB7A37B
              D7DA6D686CDB84E02B26A2FF1AC6445711069D09F1246949F3E1F3BB70EAEE09
              D4369D063C5859F71DFE0C174F361C2879DAA0F0082E1A5D01120239BA00FDA2
              050EC106DBC005DCED3988330FD6C3E2F80B2B667E842DAB2BA033A276E16694
              87B3C7860D0B39EC626C607574AF8732461266D83D4722C5000F9D7568B06E42
              7242327E58FB23F446EC2BFDF64510610170F4D4CF77429B00E8E2016D048921
              99949C8389496F62426226E20C29E0B4E401011964FA71CEB691144AF8724D85
              0C6CEFB46598383607B6E098260E458140741960D0E9106F94903A598719D929
              D0C5F2707A6CF0084EC8591ECB27A068CA36FC71F9286AEB4F1FAFDB8C35B44C
              18350B484C24C9A1341D2B937217619ADF03296D26964E48C78A79B3D2919793
              82A7EE36B8847E04084496B104E98665D8B467039A6B91DA76165D18C5809BC4
              42D23D06FD87B6B1E514EED31863FE170D93A7A3DA3568FD59AB314ECECAC883
              6FE032B92AC13258879CC435289C5E088FB3A18A007C2A47211C07E4D038491E
              AB20C6123BC923122B491B95818BCD47F0795DC33D229201F19A2C30221020AD
              5D03E751905D0068B0080A4B4621E14BFE82D508F0A9C03B3B6FE2DA136BE0D8
              F53B7624F019CA0C86F8D4EB6A464E9A498E6BAA1CB15705E079303290DEC7F7
              71A0C36E879E4F22F783009C3E0B04D115AA463CA224D9FF01E1D12750124802
              7849A7F29D40081204C13D8258FC381D72018AAD97915870D02B1150908901F8
              2902C311B0E304804DCCC6C7E9290910FC3E321C6489969D40641C19814800F8
              653B50BBF22725A4312F619C79772DB2F5F1289F9DFB1E1C2E3358322E67829E
              4BC1039B19011F5A4207D36800B8D24A1C9A9B851562307C71D11A9FBB019989
              7938B9E4ED694889CB44575FA3E23D477A0C04E09ED50CD18DDB6AE684E50057
              5289C3453958B57AF6D7A86BAF949F6922192DDB8EF77D2E888C16EB780DD697
              BD938F05F9ABF1C07E047E6A0AE4981B634D707BFB71DD6C415335AA689D371C
              00AEE47B1C9E938B558B0A3E21F26A6911B0702BEC4C849AC89196A9596FC034
              310985B9854836A4A3A5EB201E3BEE2A27AB868D41BC360D975ADA30F00467FA
              AD4AE1F23E7F1670A564BC281FAB961494E386E557CCCFDB051F7B924E479E9C
              6046C939117A7639A480089F3888EEFE2B30F71C8357F02AFBCBD065927106FA
              DD3EFC5EDF82C65D98D367C52D7AE5180E404361BC333B1F5317BFB50EB73AF6
              29A798A436434C14FDE0F0496A6FA8004F8CCBA0EE08A83EDB06CB456CBC7918
              07D4F22D0CDF82584AD9A9B3F266A0A5A71A8CE699BE0013B9311DB2CB8D4C2D
              2D6F40AC3611BDCE01D4D4DBD179035BC9F871B94A62A8343D03A0F139F0CFA5
              F6DBF34CA941ADA16E9D8DA254310CA7AC61590E3CED770CAFA58A17C095D627
              686A76C3760915B78FA246F5DC13AE21917B80ACE2AFF0CBC20528CE9C421045
              15A1961433911B639E8BA5499232C7DE2DE1A14D40AB5980B31BF5D7F6A3D2D9
              8556D5F82086EAE24800B29F8972234220769694A038C314DCCBFD87C8000F30
              4C74854070A1DD3F807B577FC3EEC11E85EDDD6AD83DE136931FD6033C956FCE
              55E10B1A76962E45714E0E9540E2C3DF1528A367FEA8CE80607A39557D32D35D
              C3F77C3400502BD31008727827FF218AB920B9CCA17751F6065E5584B157BCF8
              6DC8A9FDE0CC926F70E183E0593069BCBE0DC335A52110D449204DF5CA1A6504
              5E1980D0F6E8D5B476AB9DCE38B42FAFF9F3FC3F01060071E9549253EC6B7400
              00000049454E44AE426082}
          end>
      end
      item
        Name = 'arrow_redo'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000058F4944415478DAC4576B505465187ECED9B33776D90544
              2021948B77B4189924958612C674B462EC364DA356D38FF8E1643579C9699AD2
              D26E7FFB5162A3E59846CD948566EB6D065273E8021A0285CBC2220888ECB2BB
              9C3D7B4EEFB77B56575CD84533BF9977E6DCF67B9FF7799FF7FDDEE51445C11D
              5DB711806EC5C75096BD8FEFE95A18ED23FE36C6660AC840490E96976DC53EBA
              D7FCDF00B462005859BC090BF351B1782BF6470321C4B3D37D2FC292948B0F65
              0E4B296159E1AC7163A596CC3B0C4830A0BCF0190A754F05B660BF6D339EA057
              81B800DC5F892473163ED3EBB17261FE021466CFC3CCF4D90801D0C4458397F3
              A1A1730F9614AEA19F7C5EC111889F2340704C841C77432C7CF93B58250BD8B9
              A2B00CE5B39642A74D80B3FF18067DED70937104C0AFB4C7E461480E7DC15CCC
              C97A1E3F3554A1AE11070E6D42053D96A231C03FF42656EB8CA85AFFC8064C4A
              CA464B4F351CFD36041475B330FF5C98ECE88BA357BCEE1AC4E6DE2F317F7A01
              7E696A5C4EB74632D748007CD95B58A33761C707AB3E62358A3AC74678C42BE0
              68230D772DF70A178A2A6699ABC6BE9585619CFAA711E2208E3391DEA08119CB
              3041D161C7EB8F6F206F0A4ED85F0B3932B08C7330EA52A1134CD0F01AF084E6
              8ABF75CC04C844BF24AA6223C95CE8008E1CC38913DBB1961EF9470210328BF1
              E98AE23264A666A3B66323146D08B9414844A221133E8F84FA964BE8EAF661D0
              C5911646570013AA2401AB9F0C5DDB492E478E069DAFA3D74EA6CFEB00E49522
              D568C2A38B8B96A2D9550D377F05BC9E122558916CCCC3F9D64B387ECA81CB0E
              1C70D6E3A0D600AEF9309AC61081F6E16DA821EDA2B515B0D9AE3A67CABD1CAE
              82300021A714DB17CC5E00BD9080F6211B780A4DA0F0538CD3D16677A3E688A3
              FBEC3EBCDC7D16E7E9FB413251A5511E0540B286D1EE20E707A33B8F04602049
              94CFCD9D8B8BEE5AC852A8455A8C39E4C20C5BDD19FC558D4A725E4F8FFBC97C
              EA26F25865C000D87EC4C9E3A3388F04A0A364DE953F291B4DBDD5E0E490D4AD
              C264FCDAD0833E87FC6DD79F41E75D6AE4F19C60FEEF5EC13D6AD138A339BF2E
              056C4729E0814B6CBF0AC028A4A0A3BB01BDCDF84A8D3C5EE76C0D91D95596BC
              D19C5F2742065392BCE024E5EAA782628067780801111D2AEDE339BB45D5C65C
              D74E4342E02706147686CA21DC02352BBDD6087306CCA34570AB8B8F64402606
              F47C72D09542E6F78BC848B622690A9E8EFBF4B95900E4B0A7A5B30D46CD4470
              E49C271BF4B4A16456110C16AC99B70AB9314E9E5B0220F95DA86D72B4C14C00
              347288F08B03A731D134054BEE9D81A4E93854F22AA6FCD720C2C7B1D99A85D9
              25EB70B272C90370F92E60C0D31E945C6AE22C4C4D5F89A3E7AA51F3DB39428A
              4F946154E912A0A9D980D3E314E6A800583564946EC2AED2A2CC07E74FBD1B5D
              03F5244A31D8C7D32C73302DFD29F4BA1DA86BAE437B5F3F3AFA3AE1F5C7E744
              C307A9FEE1E07A3CC6D88E06805D5B2C9928285E8BDA67174D83D5A8438FAB11
              8A5A147A418F9CD40AA4598BA0D398C0D189A811E3CB863681C7FABD2FE08B97
              606133C06833A167B013F6FE266CD927346F7EAE3C0F29C9791818B2B3F2A082
              1E4653DFDEA021620E89351732064BA7BD171C66822D7F0480C8A9985173F9CC
              4EEC76FE8E77AB0EFF8D7EAF1B566B060C09E6D064A38F306DC81087B9256718
              29176B2A66DDAEAB7E3776150C61F06BA97B5BE14C230AF20C484C9800511A86
              248B34680482E1294AECDE149C8ED149298BFE7E240059EDE1CEC66F506DAFC3
              1FBED5DE371A5BBC8BF273044CCE14909E46FD4821A3199D9D1DB18A92011035
              5D1084B1ABE086E76ABE52C8D24CA998448DA8526BC60C1A1772C75D6AACCD0F
              A1D6F6767012BE140F804886125885B001832C9115C44DFCA362FAEA556702D7
              78004402D1ABA6B9896EA8A8FAF28EEC03B8D37FCFFF156000D52A23346A225D
              690000000049454E44AE426082}
          end>
      end
      item
        Name = 'page_white_copy'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000003004944415478DAAC57514F1A41109ED93D29B6DAE08304
              48936A62FF817D11A9A4E91B7DA1124D4CFAEB1A510C287DEA531FFB3B8AB436
              81D486626D8D786C6797BBE3EEB8C3BB3D874C16F66EF7BE99F9E6DB0301C068
              9D9DB501B122C663101066F20A024304D3343FEED56A359AB88307B0650220E2
              58AFD713874747A7B496277DB8419EA63DD58FAF9D734A0406C74FF7ACAF3D87
              0FF53ABC3F3880D7E572B5DE687C3ED8DF7F9324134CE6D54E3B674CB9E1737B
              5E2DA07130F80DB95C0ECAA5D24EA3D9ECD2F44212008E216DCE3807F4B99AB3
              00C8FC2C3E5E84CBCB5F90CFE7E155B1983F69B53ABA203C00182792B110E7D3
              D23C4AA5606979C9C9C4CEF676817874A103C2B00A3C890E792807504CE65F6C
              6CC0E1F1B1CA845C35A6CE919C205B257F423E880FC0E1008603A0E9ABEB3FF0
              727353B9DF2410B2945E06EC12200B052043BEF97BA3DCD51A2A0BD9EC2A8CE9
              3B95A127AC39B76E90F577ABD567348EE60240C621ECF93601FDAD69CF99E61D
              ECEDEE06AEEBF7FBD99366B343E2B5E607E12121C709E2A8AEDA13992394DF2F
              7E40A7FB0D3AE75DA529D2A46E64B35928158B056AD9996EF1B62167AADD6239
              672E0ECDD78DD2D6D60C086F1B32D4F2691B73C7E7E846C1AD1BCC4F421D0F0C
              20A26EF84888890E16545D241421A2EAC64C1BEA9ADC9C53D442A0D2B57B7563
              227EA919211271A3F60440F547A903E25EDDB0D5D7F0EE46E4D1852035C1EA0C
              47DAE7E846B01473B4D7C6A8BBAB0B2C7D10E13783FFA2E15C5000386820F01C
              E7EE0C443E0B1863811BC6CD84DD827162302647ADB83A6DB797153323AC96B5
              A4175310AE7B33990CD59700D04760BC0CDCBEAB5677685C09E04D902D90887C
              7A5BA9D847B063E6D854D28680B1005CCBF751F28B886B5664E48BE934DCDE8E
              9C2CA863382E7F2C00A3B86F31D30709B0692DA98311F833B70D755E29119348
              5742004975431FC043E886356A017808DDB0F7D00240BA3124DD781A5537FC19
              90723D1C0EBF4806EBC0CF90AFC7D08D2093FF257F9277753658B0FE80A412F0
              57A64D9ED3FFFE0B30005FBC5824214F99CA0000000049454E44AE426082}
          end>
      end
      item
        Name = 'cut'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000047C4944415478DABC977F6C535514C7CF7BFDDD1509C140
              042386BF100145C118B25565365B36DC52E350A65170EDD8346A485814B2604C
              104D5C86218640A9E910580818060C177FCC395A9530361DEC473BFDA3DDA82E
              FD31B6755B7FBC1FF7796FF7AA1D14D69FDEE4E4BED7E6BDF3B9DF73EE39F781
              200810B32487F4DCF98B97C90C698E789F741ACFABB1692FB47ED39209446CA4
              03A04008C1BAB56BB69C683E9D31443A0014CBB2F0F08A87402A916EC1F7AA6C
              02485B2EB4CE1BDF58BE08022293329B00D1F8369F3E73EE5E103C42F133954D
              0005CB7250B8F9B9178E9F387506DF4BEE22C1DC398B0014CFF340D334E80A37
              EB2D4D5F9D4D0441921061F991A844360190CBE93CDE75AD1BD42A15E874CFEB
              CD96A63B20480EB02C9F4AED481A20B4E783BA06AFD737D63F3804796A3514E9
              747A93D9320782AC9CE7D89C2810C6E6D9F1C66BA5434376FFC0A01D34797950
              5CA4D31F3199FF854048000EE74A16FCDF01C0639BC03652F5E6F672BBC38121
              1CB040A381D2E222FD17878F3493DD110D01C79160640C9068ABB1D8FCE4C258
              B5A3ECE8B12F2F6247F73FBAFA11A87851BF55A150AC23CED91C85E07608D74E
              6355595F5F7F341CD839BCFE6AE52AC473D11CC8C5364C08515B632CBF7EA3EF
              D66FBDD701710CC870A468840D504E01E2219C6FD75697DA6CB64EEBD51E68F4
              15408979146474EE01E6407CB8AFBECE31E89852A11040C00F4F3EBE163E3E7C
              CAF3D881015BBA5D31D9876210728D4258D052A981F68E1E18F520B0CDAC0419
              C5E7AFDFDDFA32C533838A854B3FC795540B02CE50367C69CA6DDF7EA3E99DF1
              BBB6D6F86A4651F3F69525C6836D9EF5CA1178ABB6A6A4F059ED8A9B4FBCFFCA
              A2C5CB9F9110465C9E299C1B02CF0585C8F48844AE5A45093C70A129C39506BD
              859490F86E9AD679E0DAD4F288C5B7915CBA7EECB47EF74763691D333E6C8D39
              27F3AF1F69CBAE7C5A52CB4C8C5A49B592C995E60DD5470B1275CE540104391F
              F0D1028908DCC2F61701F9BDA17C5764EC66140238669A14326C7F761DAA7CCF
              D96E322026ECC95BF44027E9B66901AC3698163FBDBFCBBE697F975726913C28
              9905203A32D8487C477A0EBE44206C388C9AFCFAEF6D22A0D37DF56B6B78DCDD
              01B38717753A49285FB872839F421C1003B2FFC9FCDFE04408E83EB46D57FEDE
              6FDB298A5EAADDDB36C1878316810DD232D57DDBA2E149E06F3E05241BEB3B3E
              238EFB8F55EB7FD9B7A91885027F537301E27B88FBE703C545219FAB0D1F18E4
              52997C27766E042E32E9EEB964106153524025536ADE1598903F30DCEB20598C
              5FBA0C665773FBE044D9856E53F51E3C7F12D7AD48CCBCD882A90228C96A1117
              9EC4D763D12CC6CE1328105F2FC64447CA3885C9EFB87A412455003ABA5A2CA1
              28B374361718FE1ECF90FFA645CBBC1413870157EF4922E753356603B99FF10E
              37C78A4AA663BE4AB8A4A0FE070F51810F4E9CC505A502EFF3C9CB8D5BF3C916
              C33693EEB761B20A70BE819F769355CBE48A0A1409BAB1739D9850E1FF4301F2
              D9B58C2821E60B59F1A8D898D84CBE8E9305A0C5F2A9120FA48C98E16C26AB8E
              F7F98F0003008EDB467AAFDA84D70000000049454E44AE426082}
          end>
      end
      item
        Name = 'paste_plain'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000005414944415478DAA4574D4C5C55143EF7BD01DB982885C6
              4D8DFDD91861F8EB404C050A52CA8F8C0960DC69D25D6961444AAB48610CA428
              B5B548A7D646A9691A77251693362E5CB9208D1B978D26465B8D0B6D8D66480A
              33EFDD7B3DE7BEFB1E33C37BCC50EEE4CDCCFD3DDFF9CEDF7D0CF2B7502291B8
              691846544AA90618632084B8158BC57AB16BC3165AA88035DB39E7D1BEBE3E12
              AA06100C2CDCB811A5397C96B7028011886BA3871719C86EA905004830441AFE
              DB77045A9A1A81730B1F0E8218D02C10086698B074E70728F9F51A08A3581F87
              DF382781DD3E32F35D4F3E86424A0BC1BB7BDE88014700B81129A6091BE6BFFF
              074A763C0DF7EFFDAE40E562DFBDE739B06D0E3D6F0EE1EA90C2868A8089006E
              7E95E82E842102B08DB47BE29917E0E75B53883EA46C4C00246B86B2B29D04C9
              7773695919AE31E1CF1FBFD100244861C3F3D1B8628CCE2E04007A14A0F6AB68
              63D2DE540239CADC55FC10AE5CBD0E4C72DFCD247C57F103E0788C90A606C0D5
              5938009E4DF239A164128465110E20EB9119A434A0BCE827A828BAAB68CD962C
              3D3308660097B44BA89DEA934EA13256E15140E7718B3649073373047020368C
              6CCB4B84498C483B0B88D4079109786A1944EAD1E60008F47415044C0613870B
              0D14FCA0F42024B7EF431CB9A691CA0CBFDC5D81D2CE33B0D021FE42448A95CC
              B0A328C185B75FEBEDED098196C9AD349248DA8940D3912F709C5B46E1AF470F
              6F25FCE1EBC54515259A01743A3BED98008219609A72C91DFBFE76EFBE8A1815
              B73203B7D45F8CAD639018DABB6737E8ACBACD7342CED38E090A00E0B6A25008
              4CD3F40E57D4AABF8E2023A3EFFEEAF0748DC2426ECF26136464BA42009808E0
              CBABF35051118686C64698FFE273282FAF5029BBB1A9C9EBBBC269FCC503077C
              9C90E21E0148E104532003221B806130383E30A0FED3E147FBFB95D62E03FDC7
              8E3941AD4D2430475896ED538C881A15BBC2C94A2CC009055F736505C0842B97
              2F434565A5DADBDCDC029FA97E58294320D4D8A797205C59A5E87FA9A1312B97
              68004CF90077235A068761667A2306066231A5A14BF1F1C14130B402EED860EC
              2DB5860058B6ED67020976DA890206C13E00B926C02C78299180AAAA2A9D8605
              B4B6B6C1C58B736B63D2199B9BFB042AC361F48D83FE3E60D929753EDBC00973
              1D94BC7E68F88462841CD86566E8ED61EFE22275480E9F18410604564F2B2015
              7B0C0004DA2087012ABBB3E7CF414D6D2D1C3AD406172E7C0CD5D5D54AEBB6B6
              76989DA57E8D17866482969697D70320AD6DCB75C20D8A987761F1BC104EBD3B
              EAD97BE4E4293DCD94562327DFF16A84F201DC6F5B568009280ABC3A240B3281
              693238FFD159A88D44147802D1D1D101E770ACA676BF179E347676664631D5DA
              DAEA7F27240654E8B04D38217E46DF1B73620769675AF3D1D1319D8999539E71
              6C6CECB40263FB4701608248AD55C33C00DC346198064C4F9F81485D1D747675
              C287D3D3B03F52A70475BDD2051FA87EC4A986D2F181F6F676BF44442670ABE1
              06971829D685613C1EF7AC333E3E91353F3E3EEECD69725051CB3F13DA2E0305
              E4012323114D4D4D417D7DBD9774A2D1A8EFD8E4E42444908D2E64CADF09ADD5
              BC35DCF54196D19F988867CC53B593BE63F1F8FB1EA05C0032F928B5047FFCDB
              904FBAC06445ED598F25A90A4CEEAD882EB74163B9658600AC9EBE7EE728FEEE
              2CF04DA968E155FB5B270CCD0DCBB77F456359BF2470051F7AF3F8BB906B34B6
              1D59F58231789CE65E5642FAD5697933EF7898399378A77B2ADF05268801AA96
              C9647209368EB9C05682CF5E62A240C6FC1A29FD90987F9C038AF079129FE22D
              5C8A89360ABB95FF051800B0FFFD8B3C6CCE880000000049454E44AE426082}
          end>
      end
      item
        Name = 'cross'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000003BB4944415478DAAC576B481451143E3BAEBAADADAF7C60
              8A61AE968F5232244BCD288914C222C90829038504230AA21FF9CB20E9874481
              45420FFC915194051965A2A9A4888892CFDD35B328B56C955D5DF7E1AEDD3BEE
              C83E66EFDD59BD7076E7CE9CF37DDF7DCCB96700F89B4F674EEA0A367C0D9E37
              8F70D8204D670B6BEB10E111CE6A50EBFB959FB909ACE16B0F4408C7A9D91D1B
              861DE63FBE590BE20CDF1320C247088E08FF5427C7846786044C275FAB84853B
              95BCA89B2F57C1E0ED2AC86CEBF7455D2381DC200447C405255DB90EBADA9BC4
              A149CB6FC0504DB52B111EE130A8EF876FAE984C2062BC88B6F4E01624565C05
              4CE4B01C2C397E867D683898CBDAFCF00C04218B4700DD89172F81A1FE1E7591
              7D8B2B60F8FE5D6E2658411EC4EE435D85C83A9230643108A83DA1B41C4CCF1F
              5281BC4F97C1485D2D7B2D34069167A3EE04B23F226E0A6D45EC3C5F0AE6C6A7
              54408DD1C2FEFBFB30545FAF827330FAA4CE8E9CDB84C02BA2B8042CEF1A6023
              1A935F04A3F58F9DC8D75E435722769C2906687EB53EF6DC9330F6AC9E979C4F
              80B388C222603E3779C46D399807632F1A5C92BB12E02422FEC42910777D1244
              BE9C710414AF5F12C949029C451C2F00EFDE76B7C84D7BB341F1B6914A8E9B98
              8063B406AE261CB3994D226E35E46B6DBF48E4B41958CB7071478F8164A44FD0
              12E813F680F2C37BDAD9415E024C1E7F381724E3431E6D427D6C12285A9A8922
              44C491E71C02E90FE5BADE425D741C28DB5A5D8A10F1D505E9C1B299B8AC2CF0
              9B9ADC9044B418B10D941D1DBC22EC047075813C633FC8FE4D5181D51A2DFB1F
              EC2FA3FA6AB74480AAEB8B9308C6893C3D1DFCE766D08E6788A60D0C85C9E959
              D6F035CD1F63626CC7A35C6C479E9606818BF3E8E420BF6EF31219A87A7AE042
              EF58A1626169B113A0898DD56B8971181BFB217F835345244F4D8520B39E3A95
              738C2FA80606A0AC4F913FACD18DE15A0659244E56F2941408B218E8185E1250
              F5F7B3CB21E62A22302F53138DDA22B2251F44B766AC028C38EBA191B5CB7725
              4330B3424954CB6B1511BB077075A2FA3A086A93D9E51AE267D8C781DC609331
              27B0087771AC1511385544F2F838089149ED04CF6A75A05228F9C85D9E1D241C
              6A45248FDD0EA1C181EC83BFEA79508D7FA39183BB388E0714B7E8F8F4C03BD0
              F4E8FB746341806F89649304744B7A1434E12EB91D4EB75AD37240C29CB5C571
              E774C423884296C57D5426FA4BF3503F1A17B4423ECD700C8E75C08972FCBA22
              554491D6E7BFDD18396F058E2C1CD9569BA379464845E4C7A572D271EAC64C10
              71FE0B300056B45360DE4C4DAF0000000049454E44AE426082}
          end>
      end
      item
        Name = 'find'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000005104944415478DAAC575B6F1B45143EF6DADEB573D904F1
              424278E1A13C95F046881002AA824B122948485CAA20D1A62A6A485AD4AA54FC
              0024784208212191427357A4148A446902955AA89A46458804252451E292566D
              EE8E637B77BD5E7B3967EC7537EBB51D3B8C7434BBF67766BE3D73CE37330E5D
              D7819AC3E10053F39C3DF7714C8DA9A0C65588C7E3904C2421914840424F828E
              CF3D17CEF388534BC4B34673BBC0BE952593493874C80F5555220EA842242C41
              341A015992E0A79FAF308C69C062F199968B809B2272EDDA75A8A9AD054589C1
              FAFA2A6C6C6E42706303785E60983DE00B124886C3E1AB022FBC3439F9170BA9
              9E4C2D5559793944B6C35709B3077CA63972E44005DA93A7CF7CF4E7C1570EC2
              23D5D5303333037373731008DC81DE9E6F9FC1FF17D0C225E23339E0CC110119
              6D9300B4B6D41BCF90E2BB99C6948A2F180157E7C953237A029A2545025555D3
              21759007C4D5F8A5A1C1BED7F187441ACF759DFC702499D45B24D98277EAA0A9
              DA8F8303BD84D7765B055EB7DBD37CEC443B886205289202A1AD1084C2DBB89E
              DBD0D337D082189F29A43EB7C7D3D2DE7E341B8FD6DB3FD44C635A97205F12F2
              C46E6AEA6FA8A9790C42A1102C3F5886E5E594516871BDB7B7236188C90A66BD
              C27EB3C3AFACAC601C5874F96208388D6521733A9D19A37712988ECE13E0E53D
              70FF3E4DF400AE8CFE420ED978E6F370CCDD12B06D0621B2B9D979A81245989E
              9E6619CF26B3C3A79E728EE9DACD645673B95C30363A061154BA981C035991A1
              F6F1DA2C9C4D72174780E33870BBDDCC68526309A8FFECD34FFC088B1B4A78E6
              ECB9CB84271C193D130E5895E9B9A36A5386DCF1F73B86B1925B6328A9545249
              3D53CF0C178D462F5FFA61A40B5F43691FF1E8B1E39FF31EDEAFC414D0342DA5
              7B34A41309E3036E5217FB7ABE7BC354BAB665C87574760D578A55ADAFF95F85
              8AB23270F33C48186A09B35DC61A8F292A0C0C0ED1D71F4E0B0C354D1445FF91
              23EF815710C0E7F3B2CA90651916161661636D03AEFFFE5BEBDBEFB40DF7F75D
              D841C24CC0D575EAF4C5BABABAA6975F7C015C6E0E9657D66033188450700BB6
              B6B6587991A5A365CE6AA751B6A258892602EE0D10241FF4ADAC2887868667E1
              E6CDF1D637DF3AFC3D8A52AB214AE641BC1CE76C7ABEB181853C1295535A9DA3
              14AD04EC12D0F05DBA7B8FBD3FBD7F3FF937A54529AB36054A07CEE584D5B5F5
              1D79611DDCC81BFBE4852C5F22BDB818C0C4CC4C27D811603E0B8BFFA283236F
              F9D811C8873748CCFC336BE01CB665680D61AEC94909518A57CC529C2F2A6612
              D6B18B5242A311810F508A0593148F8EFD5ACA50B908380A7ECDAC458A1F7E99
              636F04EC362073F61B0A994F8A73F9E6DCF5AC04266E4D30A789F171D64F4E4E
              B2DFE7E7E77648F1575F7E71A0BBFBEB0303FD3D7E63F242BE79091883343CD7
              90EA1B1B595F5F5FCFFEDFB7EFA90C016C01B4A9B4050CFF42BE0597E08FDBB7
              A11C4FB26528C324BDA4689188049214C13E65A2584DD020DAAAB93A8AF0B527
              4083B4BDDB867ACE333D97B1C4244966970B194B8DCE7BB4E6FD0383B6E5598A
              EF0E0214DAEE6FCE43351EAB2B31C325748E60AD47235176CB0947B10F47F10B
              7DD96B59A26F1601CEE9C29B0C0F02EE6A74CED3B43868718D5DB7DC6A0CF77A
              CEC801F83F7CCD0474647AC32BF81AEFDE5B82C09D40E682499B131DB3B1A0D8
              FAE25ADEB09C324AF6351F48E876F304DAA3051492B651DAAD962C37A3A27D69
              6E3301577A9B140AC8193928E99B8E668A64D1BE34F77F020C0024837CFE1429
              E9010000000049454E44AE426082}
          end>
      end
      item
        Name = 'text_replace'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000053E4944415478DABC576B88555514FEF63EE7BEE7DA98A6
              C6A86951DA28A1A961649044415A282548FE19B28751F4FA55E25B240389A0A4
              1F1685E38BA07C50031342FD881AF091056386529325C668E3BCEFFB9CDDB7F6
              B9779AB936731D1DDDC33EFBDE7DF6DDEBDBDFFAF65A6B140077E7CE9D079552
              8B7DDF873106D7B3D10EB4D662A7A1AEAE6EA9CC25EBEBEBCD8D6E62536CBB7C
              44E5E4D25ACEFE09C551CB433A97082123C989EC3775CA64146D4605802AD1AE
              494FC8D108BB1C89C2E37CB66050F047CAB8E9737171546EFF050E7D230056EC
              6DC55F1D1E0A9EC1D1D7262295F7E19B91F1BF5FB6912E5B0143EAF7AD188F58
              5821110DD87009CA2123D28525752DDDFAF7BFE69623344410A7E1482464B510
              0B51B1FCF349994757E4C94AA1A88DAB69BAECFB6500840551609400E4F4EF7E
              DF832F7EC9584DCEBA35848D0B93D407818C902E0600127A038A29CF680831F6
              962E60C7929B317B62142DDD0A6FFF9046C4D5708BEEB89A3E2880FEBE72E598
              F4FDFA8792B86BAC835573E388841D9CE93056A88E766DD74A0F5B0743BAC046
              2A6E9A4EE72DED63631AA99CC1CC5B42E84D775ACCD1508C8B23BCA6A28934AF
              692E10856C2E576D1891632000A70880633A9D2BCEF1848ECF0BAB9121284DC3
              88C5317F9DB2A23CBEC62053C870A50F87B7DA3359CE17822826508A816C30D1
              9631A011E890A74EE5ECB5CBF29831527FE25C86000AA88E57E1C12D0A5FBFB5
              89A7F75157AFB06FA5B1CE9CB559E1A7F534EAF7A03395C7A898433006390F76
              AD67853B840B4A0294475EC21F4FFFCEE17FF0FAC2B1D87DAC8373064B6624B1
              A70968F879030315B076F90B984B40E110504DCFD46EF983862E51A43E930E30
              6D5C042F2F188307EE48209D2F81A82042F1ADE0D8FAC4047CD5DC8579DBCEE0
              CBE64E2CAA4D60E5FD093491F6ED8D8048A1E9F40E6C7F7531DE7FE531F804F4
              C98AC9F894FD9E9A28AAC21AE73BF378E3C0DF683CD56D6F8F1E5A84DAFA2BEB
              291C7F73BA0D448FDE7D931D655E4273DE2B209B0DE3C74D06F33729AC7A0A68
              3ED7804935332DD5F3EFE4990A492409EED93D67918838FCBDC1D6C3AD787CE6
              68AEF18676814D14A42957520D7FACFA65329B33C04DE41A3A6421CE8FFCDA85
              96E03D3FE70874DAF808C3BAB21135CCF90B9D192B6EC9374347C292B17E1F4C
              194B9AC66B572B247921B6EF2E01EBB50C085A1BA42261BB5F840CC86BDD1D44
              D98A71A062469343FA799CDC4C6674BFC9BED1A0BD278F0F1A5BE9F3800149BD
              25715F330069BE292043455BD1DA34CEC84963EDDD79BCF7CD797C76BC0D736E
              8B93A920A7B0D0EBCB336AC850EC04E9B252975F1945A1280F8E6BE0D2151F7D
              771E4B3F3E8D43CD1D787ADE18EC7DBED6664E9F8232A51AA0723AD6184E01E6
              3ACAD2BBECC35F7131CB58100DE3E19A38362E9962F7C9316E4848B7AC591012
              E8CCE0001CA907AE348D8AD8420E361C3C8BD6944132EEA2AD338D2DCFD4160F
              41631C339942BF2B348C5B501180A552E3F31397306E5418D94C0E5267C6E351
              0BE0DB536D3C10634A3617E40313785CAEEE880050C5C2C506299B019555FDDA
              03BF21C1DCB1EFE84554451D0B4A0871747043F69F68C393F78E43C9D4A0F5C0
              95E6F438EB866C5E0AD8C052E3C976EC3E72016B164D62CD5D7C47140260FABA
              6368FABDE7CA0A928A008A20F6BF34C32698F654011DECB3275561FF8B33B0FC
              BE09584D10920DE55D57CAC3730B2660DBB2DB0744D581A158EB61D77435A3A3
              38B266CEFFBE7BA4768CED156B42A75C1937A0956C9618E8D9B56B57955796A9
              AEB3F19E52F4AE669FCA3EFAB272E5FA355140BBFC3B2A0659CB20C11EBEC15E
              90A2B3F75F010600DFEC74FC5EDE99D20000000049454E44AE426082}
          end>
      end
      item
        Name = 'zoom_in'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000072C4944415478DAC4567B6C53D71DFEEEF5B5AF6FEC388E
              9D10874020ACA12B4D9BD09586A1F248409BE85A404155AB6ADAB44E6268A37B
              B081A64E5B1F638FAAFBA352A79575DA83565A3769EA0A6D69CB5645090FB1AC
              A0A4216D09D0002B85BC6CC776EC6BFB3EF69D6B674DD300AE46B7931CDDE4DC
              7BBEF3FDBEDFEB48B66D4392245C6648077EBEB2D5A76287027BBD2CD99A0DBB
              F0823F962D654C49DE1F4D9A3BEFFCE1E1212EDBF89843BA1C81C7B734076FBF
              A1E2A0561E688AB4AC45455D23BCD5F53CA27806F7E8A3E73171E1142EF5BE8E
              4C3271E2D0DB132B773CDD17FF6F0948AFFCF4F62F54A8F68B8B5675A0A6B90D
              B0725C35F9CA9AB15D2621171F1E0CF775E2DDEEE7319195EE5AFFE0A1974B55
              63260169EF232B364442DA0B37753C00AD720E57F2F87B6F1AFBFAB2E819CA51
              F802AEC547EB22151B9A55AC6BD1789C0799D808FA9F7F1297A2994D1B1F3AB2
              AF14121F22F0C0A6C555F7AD5D38DABC712BB47008C9892CBEF1A714CEA73454
              866B110886A028125C2E09B224633211C5F0C50BA8F54EE297F7FA515EA12233
              1E45DFDEDDF8E3EB67AB9F7C6170EC6A0494697FBB37AD8874D5DFD20E2D1844
              229E46C76F74AA508F35CBE6A16D713916855424722692390BA9AC89A1988673
              F535387BEE3D6CFEF559FC658B499241088C4D99FD5D24D042DCFC9508C8534A
              FCE4FE9BAFF7F9034BE6DEDCCA7F33D8FE571B6595F3F1CDCF7F1ADB5656636E
              40C1986E206548485B12520C89325542B5DF85850DF351D7D8E8EC117B0586C0
              12984EC2944040696E08FEACEEA6E5809141E75B362EE801DCB2781E96CED330
              3699479C96E7F8F9177FB01BDB76ED8125BBA073A34E177A3C20893A445189CE
              01CBC11058027386CA9725E0F5BAA57595B5F3193659BC76A60CFE40086D8D7E
              C432069286052A0E83C6F87C3E787D1A4CC585BC2CC356647854173C6E600149
              BC7ABACCC11058025360974240657E7B7DA12AC0CCA17FAC1C9A568686B04AC9
              6D5A4B23DC6E588A1B6E55A5C52A2C95277A3D0894ABD054056E8F0B914825F7
              FA89918583454C07BB8420944D91E222DFED1C54D50317DF2485EC56417661B9
              385CF5125351F0C4532FC1247F83F1B0F5ABED90F53C728C0F410E76DEC132AD
              0F1979E52CB06C7E675167CBA0B124204B48662DA46D61BC0A990AB8A880385C
              7679082E39D8365C5069BDC9D3C492C2BD300DBE330B98A5A661A162980E09D9
              A339799EA4E3272D0BBB767EC9F1B990FD895FD172D68D9D3BD63B7C4DCE0CAD
              57180BC260D9AD150C71992595C2FF50A445D9E4F0B053E29AAB924EAD1F8AE5
              98EF0603318BF1491DB1749687CB8EF4E20CBB88E0E2B7924B463C9E474B75D2
              C1105802B354025634651C1ABB781142C7B69A7F115525812C4652798CA54DC4
              754A4A9985CFF39690DC067F615905E945351D8E1A688F70AF2D41608DA78CC3
              B33490595D903B3C30F2FBDA39FD6B1B9634A235741A07C69B3092A39C9306BC
              7CA82CBFF9BCE9049CF07986454958EEC42E2DBE3862208C0496874F934D394E
              F6F663CF81338FF175B61405F4A75F3E79643C9A7CF74CFF5BB440C1B7EA5F61
              4497B18E6A3068AAC59963566433394CA673C892809E3718F916DE1FB131366A
              E13B0B5EE35E3706FB06A048BAD5D9FBFEA0C02E8580A8D7F1EFFFF6F857DE3E
              7E827D208180A2E3E1F9CF608E663013C2481B2AF2AC093AFB40964A647336C6
              27649C3EEF819C4CE0C70B9E45C0AD231E4BE0CDA36FA0FD3396DCF58BB6A1AB
              95E2E9DD9039869AAF6FBCF1DECFDD3AEFF13577AC464580396F65704C5F8A9E
              CC529C32220534BBE0D846E5126EF31EC7AD65BD3445436C42C78117BBB1E653
              51D46CFE03706C2BBA7B5C58FDBD4E518C72A5DC07E86DD46DB9F3868E754BE7
              3ED67CDB8D58BCA4C1A96CA23EC036A7B5781179E232A23801FBCEC039BCD973
              02ABEAA38884F9FDEA6718611478E0DB38F80F19ABB6CF4EE22317124E1F67A4
              AECA77DDAEFB973D5515F42F6C6C6AC09C9A102A43E5B08B5732B127164D6264
              3886C1136791D7E35653F03DB92EE8824FA39832356A7F96D1CBC274723B0E1D
              B4B0721612B35EC98A0D24CC59BB7C49CDF5F7AD6DFC5A55C0BB4C9A51D74925
              3B96C8FEF377AFBEB3BBF7D468F4B94737EF6FAD780361BF8A804665D8AEB17A
              0F9C4E751912D2156EC5EEA21A159C21CEF262DA4AD38AA7A8B9AC3C8871D21F
              98FBDC231DDD9FAD3C869A80C6F47515765C818474B56B79F1D0A9AE36B3B85B
              C53CD78BDFF21289863F3FBAB1BB2970060D41835D752689EF3A2492BAB9E28E
              07BB8E5E8DC0C71D9E0F486CE85E1EEC433595F8800403D34B3B0677A0E78881
              D66D7FD3645CDB21641DE11CBAE747FB561D8DB7603491412663169CD5F56556
              1C7A8E7D4534318EB26B4D600689BD24D18CA1B8025D379D668B6E92B07DF49D
              73B4F24910F88812038945189D483355B96C70A687E97619A504E1B58B8987EF
              EAB645ED62F2889BC3DD0FEDE70D18839F3481E924EA38FDC5B514E705A1D2FF
              82C014095FB1B64C35BF49C75553A5F5FF35FE2DC0009C522D4551335FF30000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'zoom_out'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000071C4944415478DAC456796C1CF515FEE6D86376D7EBF5AE
              1D3B71ECC4691D4A08D8A104A711B99CA8151492C8515584AA56A5521AB5D023
              6D5045D572941E88FE47A5A6543D00A9B45245491001D222CBCEA1D425911DC7
              401C073B2921F1B5BBDEC333BB3B47BFDFEC1A8C7192450DED584FE3999DDFF7
              BEF7DEEF7DEF27398E03499270994B3AF88B756D411FF6A8706E97254773E014
              7FE09FED48BA25C907E269EB813B7F746498AF1D7CC44BBA1C812776B6446EBB
              BEF29056115E59D7BA1995F5CDF0D734D245C907D718E3E73175E10C2EF5BE06
              3D9D3A75F8CDA9757B9EEA4BFEB704A4977F76DBE72B7DCE8BCBD677A0B66513
              60E7F9D6E24FF69CE5320929BC7931DAD789B7BB9FC7544EBAEBF6070FBF546E
              36E61290F63DB2766B5D547BE1C68EFBA1552DE09B02FED13B8DFD7D39F40CE7
              99F822AECD5BDB321FB6B6F8B0A555A33B2FF4C418FA9F7F1297E2FAF66D0F1D
              DD5F0E890F10B87FFBF2EA7B362F1D6FD9B60B5A2C8AF4540EDFFC7306E7331A
              AA620B118E44A1AA121445822CC9C8A6E218BD78010BFD59FCEAEE102A2A7DD0
              27E3E8DBB7177F7A6DA4E6C9170627AE46409DF5BF67FBDABAAEC69BDBA14522
              4825A7D1F15B835968C4C6D58BB1A9B9024D311F536C2293B75D1B496838D758
              8B9173EF60C76F46F0D79D1649462030B6EB07BA48A095B8852B11906732F1D3
              7B6FBA2E180AAF5874531B1F75ECFE9B83405503BEF5B94FE1BE75355854A962
              2C9B477CDA44D23091CA5BD07C126A420A963635A0BEB9D95D23D60A0C812530
              DD86298380DAD214F979FD8D6B005347E71B0E2E1861DCBC7C31562DD630912D
              204EA799828D69CB81CEBD68B8E6C06009BD5E90443DE2A842E780ED62082C81
              3927CB9725E0F77BA42D550B1BB86D7278F56C00A17094690F21A19B489B3698
              71E4196081FBC56450A622232FCB7054195E9F02AF07584212AF0C055C0C8125
              30057639047CEC6F7F305A0D5879F44F5440D3026ECD33A6035B6610AA1792D7
              47F342D678F7F399F770858FA550E1F12AA8ABABE2DA10317270B188E96297B1
              09654BB4B8E877270F9FCF0B85BFA459E7BC2DE34B3FDC8B402008D9E381ACAA
              90147167C824663A32767DAD1DB25140DE94580EFA730A2E96657F20C82B7781
              4D20D8141BDB84C74302B284748E3567DA3D1E1F143A5784534510F0BACE1DFE
              EFD80A7C8CDEA2379BDB4DE55A582611AD2266B96D58540CCB25217B35B7CFD3
              390B59DBC6630F7C99355790A3833C31BD7428EA2E0B2164943AA357B91744C0
              B2472B06A2586549E17B142D5BCAA547475D896BA94EBB5A3F9CC823C3BE4FE8
              394C64744C6673C8174C144C5AC17C0F41E1B71237653259406B4DDAC5105802
              B35C02763C631E9EB87811228F9B6AFF4D541F09E43096296062DAA200D9EE20
              72086ED38482DAC2EC62EA859A8EC64DB4D771AD2341604D66CC23F30C907909
              E48F0C8CFD61E8643F445EDBA24368A830D8015E8C672D186C433103EC92739B
              5A50A026E4A90D791213CF17C74CC490C29AD810D9C838DDDB8FA70F9E7D9CD8
              B97208184FBD74FAE8643CFDF6D9FE3718818A6F37BECC5A07A8A31A4C3AB066
              8C6484F3028521576097F0F9DD310713E336BEBBE455AEF560B06F00AA64D89D
              BDEF0E0AEC720808BD4EFEE07727BEFAE689539C03298455030F373C83059AC9
              4E8841377DACBDC33DC0C84D3A2E38989C9231749EBA904EE1274B9E45D86320
              9948E1E4B1D7D1FE695BEEFAE5A6E1AB49F1EC69C81E43ED37B6DD70F7676F59
              FCC4C63B36A0324C1DB1751C3756A1475F8533665D11CD2916B659BD845BFD27
              704BA097A168484C1938F86237367E228EDA1D7F048EEF42778F820DDFEF1462
              942FE73CC01E42FDCE3BAFEFD8B26AD1E32DB7DE80E52B9A5C6513FA00C79A35
              E2C5CE535C3D101BF6AD817338D9730AEB1BE3A88BF1FB0DCFB0C999E081EFE0
              D03F65ACDF3D3F890F1D4868415A5D7D75F0938FDDBBFAD7D591D0D2E6954D58
              501B4555B4C2DDFDC5139984443C8DB1D104064F8DA06024ED959177E4FA8882
              A0265492396A7F96424C613ABD1B870FD958370F89798F64A50112A32D5CB3A2
              F6BA7B36377FBD3AEC5F2DCDD17552C94DA472FFFAFD2B6FEDED3D331E7FEED1
              1D07DA2A5F472CC419A131331CD7D8F034DC49751912D2154EC59E52362A6951
              5A454939A559E229D488CA83048DF5C0A2E71EE9E8FE4CD571D48635F835A5B8
              E20A24A4AB1DCB4B4E67A6DA5C71B74B7D6E94BEE521124D7F79745BF7CAF059
              34454C4ED5B924BEE792481BD6DA3B1EEC3A7635021FF5F2BE4F626BF79A481F
              6A9889F7497063FA19C7E01EF41C35D176DFDF3519D7F612691DA30D7FF1C7FB
              D71F4BB6623CA543D7AD62B1BABE42C561E5B20645CDFD3E70AD09CC21B18F24
              5A309C546118963B6CD14D124E90B5735DAB1F07810F656220B50CE353D36C55
              BE3669D3A32CBB8C7236E1B5DB130FDFD5ED08ED62F38893C3171E3AC0133006
              3F6E02B349D4D342A57719DA0591A5FF05811912C192B6CC0CBFAC5BAA1969FD
              7F5DFF116000EDC34484CEAA3C570000000049454E44AE426082}
          end>
      end
      item
        Name = 'zoom_actual'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000032269545874584D4C3A636F6D2E61646F62652E786D7000
              000000003C3F787061636B657420626567696E3D22EFBBBF222069643D225735
              4D304D7043656869487A7265537A4E54637A6B633964223F3E203C783A786D70
              6D65746120786D6C6E733A783D2261646F62653A6E733A6D6574612F2220783A
              786D70746B3D2241646F626520584D5020436F726520352E302D633036312036
              342E3134303934392C20323031302F31322F30372D31303A35373A3031202020
              2020202020223E203C7264663A52444620786D6C6E733A7264663D2268747470
              3A2F2F7777772E77332E6F72672F313939392F30322F32322D7264662D73796E
              7461782D6E7323223E203C7264663A4465736372697074696F6E207264663A61
              626F75743D222220786D6C6E733A786D703D22687474703A2F2F6E732E61646F
              62652E636F6D2F7861702F312E302F2220786D6C6E733A786D704D4D3D226874
              74703A2F2F6E732E61646F62652E636F6D2F7861702F312E302F6D6D2F222078
              6D6C6E733A73745265663D22687474703A2F2F6E732E61646F62652E636F6D2F
              7861702F312E302F73547970652F5265736F75726365526566232220786D703A
              43726561746F72546F6F6C3D2241646F62652050686F746F73686F7020435335
              2E312057696E646F77732220786D704D4D3A496E7374616E636549443D22786D
              702E6969643A3138303235443730413735393131453142423839453135424435
              3443393142372220786D704D4D3A446F63756D656E7449443D22786D702E6469
              643A313830323544373141373539313145314242383945313542443534433931
              4237223E203C786D704D4D3A4465726976656446726F6D2073745265663A696E
              7374616E636549443D22786D702E6969643A3138303235443645413735393131
              453142423839453135424435344339314237222073745265663A646F63756D65
              6E7449443D22786D702E6469643A313830323544364641373539313145314242
              3839453135424435344339314237222F3E203C2F7264663A4465736372697074
              696F6E3E203C2F7264663A5244463E203C2F783A786D706D6574613E203C3F78
              7061636B657420656E643D2272223F3EA0450F43000006514944415478DAC457
              7B50546514FFDDBD77F7EE838702AD3012A86166A0E0108126128D6382505993
              FDD38CCFD11E363A62E2F800651C26B387E3F49CEC654E0D96260FF18F4C53D4
              510931051575145440974A7659601FF7D1F92E0B81AF16C3BA3B67EFDD6FCF39
              DFEFBCBFCBA9AA8AFFF312D817C771B7FD73DE825782A3A3876DA0C70C021AD9
              0D95EB92B94AB7DD0D0DF56F6EFEF413FBBD02E098076E03802F5857F891281A
              E727258E43525222020202FB30389D6DA8ACAC42E5F16AB85DAECFF256AD7895
              96E57E23B84D08F46BD715366DFB61BBEAEFC57849A699C9FE5B0FE8F30BD65D
              4E4C4808CFCE9EA62DD434B4E0CBBDB5D873B2013AE2D35809F3E4F828CC4E8F
              C3E8A8308DAFB4B41C5527AAAFADCD5B15453FBDF7E2017EC5EAFCCFBF2BDAD6
              6359DEB715EACB1BCBD51F2BEBD5FA56493D75CDAB1EBEE252779F6D53DFFFE9
              823AA560BBBAA9A4B2879FC9321D4C97BFFBEBBA1FD2D29F0AB3982D735E7C61
              BA66E2BBA5BFC225EBF0DEBCA918F3D050B47B39B888DDA5D09D40873E108A8C
              C9A9283D750D1F941FD764982CD3C174F5178090923261FDB8F8B1E0753AFC76
              C986D3CDEDC8999E823F3B3C707A55A4CFCCC58C85F998B3780D64BD1E6E1292
              743C12539208840DB5142A9E7E331D4C577785F90BC0A8D3F1531212C64295BD
              283A7619D31F1F851B1D5E38DC329C44255B3640A48D8DA20132CFD3E63AB839
              1501163D468E1A81EF4906B2074C07D3C574F60780818A3BC23AC40A459670EC
              723B62A342D1461BB77B892402E15558C2683D800170733A88A200D1A8434444
              182A49465564301D4C97A6D3DF46C4EE4C986D4E5FA4D808BB4B82D3A3A05356
              E1254B79ADC2BB0078791DF4465E5B2376B258854114E99974709206C4DF1008
              BDAB4192147064AD4134699B33EBDD64B8C477316A154845C38B804911205142
              CAC4C34904486F2279090A71F6A7BD0B3797A4A228649D116DE4814E72BB8B0A
              5F26CB0D2AE7EB172AE86FB25A80D7CDC1436B1EF21C6F14212B5D61EACFD553
              86B224DB9A9A9A49898AA44833AE38248A3D858088955E0701D01A117DC84104
              8223AB39F03C0747AB1B8991164D96E990BC92ADBF0024679BF350F58913A090
              233D5A406D8B8CD64E45233B85A370612E81942093B5AF672D85962E64B08700
              36D9644D4622D9AAEA6A381CF60AA6B33FAD382022222276F6DCF947DE786D01
              F49454DB2F1950D3CAC3A277D3203220204884C96424EB75E47E4E4B588F4746
              DD7917E2035DC888924138B171D387D8B0BE702CE9BE48D4EEAF075CCDCDCD57
              AFDBAE1717979441A5F83E1FD58964AB4A310E46875B8776A79B2C73C2DEDA8E
              D61B1DB8DEE245DD451509C112A6467A34991D3B7662644C0CCE9C3B57EEEF64
              EC3D8CD8BC1DBE78C9D2BD717171A159994F43F1BA71B5438F2A47302EBA2CBE
              4C25D7D36D84D189C782EC78D02281130C2829DB8D86FA0664656751198BF879
              EF2F5896B388EA051E7F01B00112CA742F5A9CB3EBE191312199D332A0A79A57
              15DA84051C7F67B8CAF1E078817240465959391A9B9A909C9C0C93D98CD42726
              E0F4D90BD877B012B98BE6DE15C42DE398880D92E859B3E6AE1E121E9EF968EC
              23888B8D85D56AEDA96FC66FB3D950535B8BDA536760A64D878D88A6CA30426F
              3060526A2A044300ECE7B7A271DF666A6AFCF8CC951547FB5870971311033198
              287C7048486476F6730B03030393044108EB0D809ACEEF94ED47BFD9F2D5C76F
              BDFDCE1741418156A3D1040311AFB7606A5A3C0619E8D456B71C07A9265297EC
              33B15CF3FB484664260A260A210AF2F5F66E4686840D4487EF1EB62C77E5A1E8
              E1C32018833046ACC178C3569AF145244511A85B42201406E29670DC0940EF4E
              69F46D7E736F977C9BCBBEDC19BE74F99A8A89517FE019F34E70264A5A818A2C
              6D0B49EBEF08E29F00F87B31805606A2B860F28151418D881EA4C06812BA60A7
              7DED0391A3816873C9133257EC3FC23CA91BA0E33DB388B5DF4BCFE6ED9974D2
              11039BC385CE4EB9CB4FFB67B296098CDE88894F8A080D321CA655B1CF2C1848
              1033F24A271D694D408BA3B32F083A59A1DD4DED5CF3B879A001F401F1525E71
              0F0857A7D4952907661187971A19D73389071AC02D208EB6C6E3929D06958B96
              25CA59EAAE1CA7C34027E15D13B3684DD601551BE52A594CA7E7FC5D29B47E8E
              E8C6FD04D01BC450A280EEB73AA2469F973CF71B4037084BAFD736AF6F4C7BEE
              F46EF89F5E7F093000FA322E6395A74E9A0000000049454E44AE426082}
          end>
      end
      item
        Name = 'control_play_blue'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000007554944415478DA9C577B4C95E719FF7DD773E11C4004E4
              B6224C51C4CBACAE2A7676D9BA2EC64BAA699AD5CE766B1B639B2D9DC9B2C436
              F8876CFB67AE1D4BED4CDB75EB1ABB31836281B64BB7D656A5F5C2660DB5057A
              28C211741CB080C0B97DDFB7E7F92E780E7010F7911F81F7FD9EF7F93DF7F713
              30CB67F5EE9A74F7DCE22774517A5487B8DC3000837EF811F8470044E817455D
              7B2D3C70F995F3879E1E9ECDB9C2ADF6D7EDF953A9E8CBAE77A9EAD2CDAB8AB0
              BA34076B166443959245A39A81335F84702ED08FA67F071189465BF51BA1FB3F
              7AFEC79D80CDF43609487757BDF9A2A2AABB7EB6A9025B571641A3C5AEEB1A7A
              47348C44F5A497FDAA8802BF84F9732448F4FFF196206ADEFE14B168F4A553D5
              5B9FA225ED76082895FB9A2EAF59909B5FFD8355445FC085AB61740EC64D570B
              D3081A0EE8576996826FE4BBA06B3AF6D5B6E07CA0BFEFF4FE4DC5B41D9B0D01
              656D5543D793F75514ECBCBB041D831AFED317069D0591950BA9593B04748224
              022BF3DD589025E1D5131D78F5BDF6DE8FAA37CF9F4C429E6A7963F7AE7B97E4
              3D44CA9B7BA2E81E8A81C3AD48B74E18C72487484B6F18FDA30A76DEB390BC61
              14884263F7E9FD9BEF48242125C6BC726FDDA1BB16156ED8B3A502E782515C19
              894326ED12992E0A9CE91644512458992F24AC4FEC9BEF58188EE8B81135B071
              452E2E5EFECAA7566C2CE839F9F72627311D02C28A9DD58B320A4AFE58F3D87A
              4A329DE21D834C6E941CB7DB906841A50D997C6C85C3B07242980AD1069370D1
              FBF756E4A1BEE5CA9D19458BFE76EDE2FB03AC58745C9F56BCBC6ED7779790A4
              88F6812829BF69B903892C576509F51FB4E2993F34C1A32A141AD95C4F7C2F59
              4630CF6AA333157AFFD16F97C157BCA28E754E10285ABB35DBE371976FA43AFF
              E27ACCB48863CE899408D26D5ADFD216C481C7D7E1E72F34C0EB92684D30F726
              BFEFC0C99F007975F3EAF95014A59C753A04A4C2CA071EFBCEB24244A85207C6
              E2A6DBC51490EC5218A7B856FF700DF6FC9E49C8D4984453594A394288CE16E8
              8FCAF23C14914E58FC48D6EDDF7167692E29D7E9C5A9AE4F7229271A0945A8F3
              ED6B6C43D58EBBF0744D033C2E850E4A1D0E3E936559C7CA921C481EFF0ED6CD
              04DC86AC96AF28C9369345642B6E018B00753F8F8A9AF7BBB0F7A1B5F8E9F36F
              C2E3B6C221492964252B21971567C1905CE5AC9B09C80615ADC72520461D4412
              525BEF809F1815511A11F0795D78A53988AA47D6E3C903C74D4F28C42095F762
              D4D038795927EB16615592D9BD8419629F087EC21A95A3AA82861459AEE2D8C5
              7EFCE2E16F61D76FEACD44B5C23849D62C78037E9FEC4C27414EECA3BCC8759E
              AAE3716391CD29689896B814D53C988D5128D5E38625E9949E6E4C6DD5922124
              CD4639715326176882919A408207A2860817B95BB065D79664E2B9373EC45FF6
              6EA30A899BABA2309580408BFD43D1091D26016E9FA311B64834F3203501CBAD
              7C92460E5515C5945D92978683B527F0FA33DB11A631CD1E717265320137E918
              8D4426F645CB9FE31D1D7D43B429DCB20224BB77C60DD98C7F71761A5EAF3B81
              37AAB6D3A544834ED404F2622A590FE9F8A493BA30E964DD7C5C3C1CEA6E38DB
              D60B9F22CCA20A2C029A28635EA61775F527F0D77DDBE9066440D7ADEB594A59
              6291460DF85C7B1FC643971B5837130807FEF1F2E1E6B6ABE45250579BD90BEC
              338D7C1C1329F38FFD1347F693F2B83EA3E50E7C2A77508DA6E20002EFBC7C98
              75F391D1E19ECFAE8542039DFFBAD0870CEAEDDCCD24BB6E93C0D941566E5876
              078E1D69C2D16AB69CFCC8971508D3CBD890E9CC0C6A3B474E76408F8E750E91
              4ED62D39D5A18D0D5D1A4C5FBCE3FBAB4ACC128A73324E1AAFCEB366490136AD
              5B48925435BA75379C6E1C27C247864528410F1C3D8FCEB70E3E72A32F1020B1
              71E73EA0D3C298BFACB2E4AB98BAF89E65F3CC9AD68DE949F03ADF0726AEE533
              2937134FC49C3401CFFEB919D77A02C7DB8EFFEE3512BBCEA9344180FFE93DDB
              7821BEF0BE07F3E7667ACB0AFD146BD12CA929B71EBB50ADEF8119409E74D39C
              CEF00A78B1F1125A3E0F0E7C7CE0E11F91681FC77FF2958CAFCD7AF064EDDB3D
              59EBEF2FCCC9F42E2EF29B6ACC363D0B3727DD9C48B987665DBA1738D8D08A77
              CF76849A7FBD6D0B1DD34318B68D4E22C0FE8CF29CB972AAF69D60D6FA6DFDC3
              71CF3717CD232B12EF83B879EF9B6EE452685CD4AED3A89AC6C21A7E79F81CCE
              B4760F92F2ADFC594118E4F29BEE52EA8422C24482A76A9BC6B297E79FEA1829
              CB4CF7A0E26B3E6BCC26D5B505C99E114CD4E332E70D8E3577E2B7475BD0D5FE
              79D399E776EEB69587265FCB537E9810E610F272976E585ABAE927BFCACDCD99
              BFAE3C1F955401A5797ECAEA9B33850FE156FEC99783F8F8522F4E7FD68BF191
              A1AE40D30BCFFEB7F5C356DABE6A275DECB63ECD081441CC25E478E716CEFBFA
              C6DD5BBCF965DF13DDBE12DD30A6CC092372E3CBD1BEF677036F1D6A181BB8C2
              75DE4FE0DBEFD8ED7E9A25EE2B369134423A2183E049B85127866F9C306427D9
              A8AD38F6FF7E9C4EE71195079A3D45A7FB3C8CDBE5154D65F1E4E77F020C0023
              BB9A6AC262CE700000000049454E44AE426082}
          end>
      end
      item
        Name = 'help'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000008814944415478DA9C576B7054F515FFDDD73EB28FBC3621
              0F936C08101202088CE0401F53476995D2E2C8C3FAA54AD1563FD44EDBE917FD
              58676C3FB59D69B51D456500054D5BA4882333748A2D1DE40D492004922C099B
              0D9B6C7637FBBEBB777BCE7FF7860D040BEECC21CCFFFEEF39BFF3FA9D7325DC
              E3AFEA89DFBA25D7033B0C49FDA1919797E5F3F9996792249100B2645C90F3B9
              F7F2D191B7263FF955F45EF44AFFEFB9E7C937E61BD6EABFAB9AD6B576652B16
              347BB0A0C5038BA62097CBC33072C81979C4933AAEF92630343A89B397FD30B2
              7A8F949CD814FCDB8B83A427FF550028D54FEFFB93A2595E78FA891558BBB205
              760BE0B403761B79CB5AF30521FBC8E68048DCC044248310C999BE1B387ABC9F
              81FC25F8FED697E87AEE7E006895DB3EF42D59D850FFDC53ABD158A3A2AA1C38
              71298C13BDE3E81D9C44309C126147D13D4F850D9DCD5558D55E8BA56D5518B9
              9944BF2F8CCF3EEFC7A83F3436B1F7A916BAA6DF0B00AD7CEBFEE12D8FAF6858
              BF6E011A3DC0357F02BFFBE81CC2D319688A0C599128DFD2CCCB79118DBC4845
              3667A0DC61C5F60D9DA8AF72E0FC4008272F8EE28BB383FEC9F7B7786F07A1DC
              E9F9FEEB9B1F5F51CFC6BDF5C0EE2383D879A84F58B15B5468AA224028B2344B
              543A63B1A8B20071BC670C7AD6C0B7563E40299261C8B26BBAF6DBCF272EEEFF
              03D931E602A0546FDDFD66677BD337B66D588EF90D12FE7C60009F9F1F439955
              23C32A14322089B84B25012C08C504328311E06401D4373E8DA9680A8F3ED48C
              643A8FF1C9B833EFFD4E43A2A7FB9059982600A9E29157DBB5CA96B77FF6EC37
              D1D6A862DF511FFE7DC14F05C7C60BCA39E9590A758A3C4C927729DD409AFEEA
              147A83CE258E840051108E887F3241C675ACE9AC433C2B51974CADB47A167E90
              1C3A36C9865533F4724D57F7E6F5CB29E756F80249FCF3CC28795EF09A7F0619
              D1C9B0C769C16FB62CC4CA16F7ACDC9DF645F1FAA1210CDC4CC056921A067EF2
              F2383ABDD5E8F056E286BF013DBADE4DAF3C489211DACB166FF0289AAD63CD83
              CDA8A16AE79C3BC8730BE59CBD6010E41FDAEB1C38F2CB557718E7DF2A3AFBF0
              A5E5689FE7107795624D58892FECE4C8C7C707D1D6508EC6860AC89AA5C34136
              F93D06A0D83ABEBF7DCDB226F218383F142552C98A62524D2F28F4C439787DF3
              C21983FD81389E7BA717DBDFE9C389C1C8CCF9DE1F2F4396A2C5EF9851E014A6
              D2590C0522A8ADB4A3AED68DB2259BB6B36D0660C96BCE67BC4D55703914F45C
              9B22D405F433552E6816F07AECC2884E687EF46E1F2E517BF6F9637876672F46
              42E94225CB85EAE2FB33008ADD71CD1F46BDC705878398CCE27A866D730DD8F2
              B2A5A3B9B1122ED23F3416269A554511993F2A6AD829ACBFD83F808E7A07FCE1
              349D29706A92A88B2AAAF8F2B25B0D65A68D8D970C0C0442097C7D991D65C413
              9262ED60DB0C40653AD51455305B34A18B7E97E5D91C254B322E8CC6706E2426
              BCB35BB8DFF3B09267DDCF2F81DB56A8E7E1C9A4C8BB2ACB0278E9C04A521AF8
              5C507811AB6A367546CF51A5F309854D2DE47D1663715B99CC27B8DF10B9DDB3
              A303D50ECBCCBDD73EF1512DC9424FA906591895046366A9758BCF24D5A4931C
              2964C52A859689E47600A53FA6DC0C8D96BFFEA40B15C5D007A775BC726010D7
              43198AAB3ACB7B133473050F2EDD306EA5CB24343E340400F25492EE48014A78
              9F39E1A156F78CF19B647CFBAECB90E8A1D3A2DC61DC04807C2102B95C6E3600
              F63699CC504101956E2B52E49EF22500B28684B5F36F71C19BC7FCA22E6C96BB
              478EBD775959771619D26F5E13631DB9E4C0B07F0A13611DCDF35CC51E96EF2A
              DC5603C1D48CF230F1868D3A475394BBBF47455C5361C708CD874422435E2407
              D83647204B2BD4C11B63AD3FF74F2430BFDE4DFD1A152998CB191149C27DEC6A
              04877BA7C499938AAE8C425FDABAB7BFC3F99957E9C499FE00D2291DD9F0C841
              B6CD0052B1D3EFEEB952DB21002C6EA987AB4C43FA2E69E05CEAA4F28575F5F8
              EED22A71F68F8B21EC3E79B3B023487387DF4E13D55566C195EB214A770AD3A7
              76EE61DBB2E8C060FF782E151FECBB1AA00B117C6D69A318B0D21CA9603E30A8
              984CE3FCE3FFF3193F9BEB3E87BF9D76C95397C61089242165128319B2690E23
              2EC978FCCCCE974F9FBF8E7357828236DB9B2A8A74CACC26DD129549EB4E37B5
              E2B3D2BB85B10C5AE99C48A773F8D7D91124A713889E7AFB65B6C9B64DFE34B2
              A1A184D5BBB63592D6161335E3E1AE3AA4A92D625430B25CD80738C46698ED34
              2FDA6A6CE2E5CF6857ECA71DD0A2DCBA271557B66AB7030D552EECFEB41791A9
              6964A7460E448EFFF13D7AC405942B5D6D9C24AD9E1FEC3BBA78515375E7A23A
              3CB6BA095747C318094649A13C935FE6119E013C944CEF0B6B5A49D1D1BFD52E
              078DF732EC3A7C11633409F5F8F46460F7D647E8E110498C2F95AE649C0A23D1
              F3D1E144DDA39B74432E1B8FA4B1D4EBA109E64424961404243E40C48493C41C
              60614A56E4A2D704826741736D05E89301BB0EF5E066903C8F4527027BB66D24
              1B232451732F546EEB960C4FDB446FF7A7E986F54F4E45D2F6D1291E2E2A96B7
              D58A2A56C43021D6E46634F705D26223A36EA70DB5E54E78DC762AB800BA8FF6
              231689C148C64281BDDBBEC7B38A24C4EDF7A56B39AFF9242D9E8DBF7F55AD6C
              D9504FA3DA53E51624E5259E68AC715091A982560B1F277924F52C86893FFAE9
              EBE8B22F84F8740AD95406B9B0EF50F0E39FFE9AF4F948266E5FCBEFFA614252
              495267F3AEEB723DFCE26BB2E6F2BACBEDB0F2864CEB1ACF0DE674DE7E383506
              D5448668D6A0C2CDD2129AD7A787A3FF7DE395E4F07F7A484FA05874FA7D7D9A
              F1BAC8854C52A3BA1BE6B957EFD8A8562F7A4CB2385A672B9184A67C2636A44F
              5C3912FDE2AD83D9A89FFB3C48C2DB6FE27E3FCD4A9F6B45200E129E40B4B6C2
              5E9C23B3088F244912291659BC6858FFAA1FA7734584370F5B718A4A730D4AA6
              D76231E7EE45E9FF041800B6377091DA1B1A640000000049454E44AE426082}
          end>
      end
      item
        Name = 'cog'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000007DA4944415478DAD457797094E5197FF64CF6CA6E08249B
              83D06892CD6E2018228311324440D4B63A63EBF41F2DB5F4B0D35A04038E564A
              31841041649C6AB55391524B0F1C715214322D393081C86473816930D0722C24
              4002BB9BBDAF6FFB3C6FDE6FFD5C36D5CCF49F7E9967DE7DCFE7FE3D4F6430B3
              4FB5E7B5D7C70541300A421CA771B62897CB6970D76D583707C7C84C1E54CE50
              005D341A35AE7BFAA7108BC5C01F088046A361027CF041B391F6915CFF0B01E4
              F50D4D6B349AF4B7E9C14D75EB73B9666AD41EAE4F8C43F7C9532093C94088C7
              A1FA9EC5104581685F7C77E72B7B0EC9E4F2878381C0DA5FBEF8FC7E5C135232
              4A65E61D2FEF1EB59496ECFBEE138F2B8A8BEFCC6A6CDA7581D6699334972153
              D25AA1508082CC8F9E100426806CF396AD95F50D8D7FCACC343DFCE823DF84D2
              92D277B66D7FF9FDE994952533DFBE6397C36AB5E4D42CBD173E3B771E6CD632
              3871B21BCE9EFD0C82C12014151541CDB27BA1C7DEC784208BDC5DB508064F9F
              C6332390933307F47A3D2CC3FB172F3BC0527227B4777C0C9F7E3AD4BC65F30B
              8F218FE87402C89FFFC5E61F555454BCB56AE54AE8EDEB038FC70B06831EAC65
              6560C830804AA9845BB79C303A360A6363D7990BE2680DB33907F2F372D99980
              3F084A3CD73F38009E491FDED7C192258BA1A5E5EF24C4538D0D2FBD2D7587D4
              2C690643C69B558B2A61E4DC39F07A7DCCC47E7F00ECBD7D8C119318994A89BE
              6BD7AEA340D76E3BA350C8D93B434367615165255CB870F1B7B8FD2E5220550C
              A47BBDDEE3AD6DEDA8B18545373D22FA9AB422A2DFB42632FFB2332A950ADD58
              8A4AF4A2453D1DC447EA0285D4FF5D9DC74FD9CA172C090483B98BABAA607C62
              2291E752A6C04793D108C15088CD454192CF9245FB0706C16EEFFD7753E3B6EF
              E3D24DA4702A01C82FD193273ABB2C16EB778AEE284A272BF8FD7E1168D86734
              6660609540195A499B9E0E96B25230656440281C8270389C1084C6DC3C338443
              6138DAD2E2DEB1BDFE51BCEE40F24C1703149D4E32914C2E336667CF8633E83B
              29F3397366C3BCB905D0D6711C8687872903FCB8AFB55AADB0E2BE5AB884513F
              31713311034EA71B16D8CAE83781D4187F3F9A0C44AAADF50DE331216E1430C7
              29AD0A0B0B211C89422C1A4D08A0D3E9A0B0201FFE72F03D181C1C38F0FB77F6
              EEE78F299F5CFB83EF9D3B7FFEF11FFF702D5A21023E9F8FDDA1FB0174D1C285
              15F0C28B5B2E31F730EC90B9B76ED9CC605B29C26BDDB31B00478C6401E288F3
              57AE5C4D9892A23B1753ADB5BD8398FF0199BF8AF726383AAA70BE0B8588B5B6
              75AC595A5D0D23E7FF95B877132D52853851BB7C395BA320DDFDEA9E046C9300
              6A42B748248CC172864183186B7498328B1E22DF0F0D0D01677E89FB32C6E3C8
              47EB6673EE9A0756AF4A084EE4727B9026612A43E350795705435311B6590C18
              0C06A0E2269753FA7C9E5E093F2915E07239F1A2E0E59A8BCC818F349FA07D97
              CBA5D7E9B4100A85790641021F68A4BFA94A2AC101A773AA801170C8246924A6
              54342620CA19C93D7A6EF6581284D33C42FB742E148A48D2918F7C3E6551E18B
              0290D62A0C0E020C6B69311414E44106C26A026490104480A2FD673F7F666352
              FA32D9699DF6E91C29223235E8B55030370FAC96627CDF8270AEF8A27539B278
              9B76BEA28F6106A8554AB0D96C505D7D0FE27A60EA304A3D39E98115B5B53032
              32B2E9990D75E1D7F6ECFE951803387FC96C366FBA0FF76F399DA04457529521
              6D8D262396EE4FA0AFAF3F8190485E69313221152165F2B96ADDFABAA3CF3DB7
              111C971D1225E3A0D5EA408FC5A90DE19A02121F725377545E5E0E2B56D482D7
              E3033FA5A044C3FCBC7C78FD376FC0CEA6C687B8FBE21C0F2E8859E0E393ABFC
              4E269D11D04F5210A28FCA31E1446DED7278F0C10730305D4693C9C4D62731DA
              090929CFA55F448840767636AC5C75BFBAF5D83FFAB90061CE97B9202269A3C8
              976FD96CE5108B446E1380C12562858B07AD4AAD826B5805130195E23C81AE0E
              FB83524BD99328408BB40E24D702E5FA673736A3B48F3CF6ED6F819BE56EFCB6
              F22B2502ACFFB64F4402971417C36587C35AB1F0AEAA539F741F94D602A9C81A
              BCF08DD5ABEFC766D3CF52454C25D67A719256BC644A754EC4007A17E75F273E
              D3594067CECD0B20FAD52E985F8E920B0C44140A15D6010D68B45A484B4F03A5
              E2F3FA256A4988499553A3D5409A268D754EF138F0FB4A0CDE743876AC150606
              06B69E1DFE670F85532A0164B8E9C8CE312FF4F9FDF3CAE7DB1832CAE471686E
              3E0CCD7F3B0C5D9D5DACFE17A34945F790966AB51ADADADBE12016AA5E7B2FDC
              C454C46616D7D3201D05FAE8A323D80FD83BFFFAE7033B783F109DAE1F880D0E
              F4776765CD9EEF72BB0B67CDCAA47E1F9BCDE18FF7EDFDDD53BDF69E03B979F9
              4FD4D42C4B9896995CA5800F0F7F086FBEF1EB87D0C77F9C95955578F5EAE8BC
              3CEC1349737B4F4FD7BBFBF7ADC3E3A33CFAE3A9048873C9C2A707074EA0761E
              C795B1A5E3E337BAF1F2065CBF4897EF5EBCE4E99A654B257DDF546BDED1D109
              7DBD3D0DC4E4CCE9C1135F2BBA630176C973ED3DA7761D7AFFBD9DB87E056932
              19C6937BF5284FC958CBD1237B018E1CC2DF7E2E39814716618C2A4D0D712C36
              AC6E21739AF30C74721307F6EFDBFB131CB57CED062F58D1AFF29F111D72F340
              B9C1E701517282D16DF50D7A2AA946A309D3D52546BE5752984889107F3FC87F
              0B5FE51F932FFB92615BEABE04BCCEE4C1990AA0E29D8C3AC59E08AF11F87FFA
              FE23C00088E455F7315A1B6D0000000049454E44AE426082}
          end>
      end
      item
        Name = 'image_add'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000006584944415478DAB4575B6C544518FEE65C77DBAD969BA0
              418C26C4079517341A21018342E526622291071F3441DE94A85144498902091A
              C38BC28BBE28F189C41841085E4045024405128948B4B4B58512E88576BBDD3D
              BB67FCFE99B3DB6D41BA209EE4DF9933E7EC7CDF7F9DFF2800DE539BBEFCBC18
              AB45A538C6FF75B98E03CFD1BB76BEB178196F8BE5758F928E08FED9BA85C897
              00ADB8A246FD5BFF07646DB70B5DE0998DBB17091EA5BF9A404A34AFE3E4E079
              BE2F139FA34E80AF24B8CA389A389552D477FE544EAD8553A309289DFC5911FC
              FEC644FD7ADED7A7A01A527032693E0BA052FC6F9A631052A510CA25539FA3C7
              D11109686B8ECAB373B870A318079AB75B3E1667847DBDEA1B276508434F6C80
              338E0C3204AF4F23AE0BE110186982854280738A017613210125A002AE12128A
              76CFE6CCEDBF5D230878CAD2D304D675D49E827A6A4B02A23952A279002DE0BE
              0FED598D5542401B504B401954059D77CDBE351170E5C5402C41E6298F26E763
              CE55D5BD0AB916F0DEE7DCE5DCE5738AA6B6AA42C033E63701C84DDD5A08887B
              3CC7868880E87018B0022C22F380A3C7D1135F5B514E022A66E7A8E0187F6AD7
              EEAB6B2120F88AF9A2A9A1010E13CDCBC0A9648D04946FB5AF8027C0764BD75A
              A150346675540D042A31200065F011A36792D9BAC04B5C200412ADCB04743297
              F4538A3C94D9774C02712506AC8FCBBE16735B12EEB0258C0BB8E65A7F2B0194
              341470292242A438BCA9E75E8305E00BA83F123CF02A2E31F7BEACF936084DEA
              8536F518C14A0509010DED4450F98221306610AAAA1830000624013764AC1510
              FAA616408A91C7BA309845A9A70DBAB71BFAD22594CE75719E851EA40FFAF350
              17B370D63443D564010946D14CACE027A06522261BA8615AD284DA759F42DC77
              96405920E2FFF25C1BD2FC1FD5A867495525E89801DDDB5F5B1D50E5BAEC0D5B
              40E6467B3FB05AAB0871D731E8A8D7FADFB3E55A17626602BDACA9755C32B55F
              4730A9AAF95E50B6AEF9BD4A1A1A577936C00C1113EDBE2113F7B503F973AC8A
              2423D5D1714C71D711B5968A572AB1281262C8B1892801589277C261173BF557
              26A0AB6340AA8688E4B9D4FA58B4FE8BF70CA84C90D406C7543813E52A36A34B
              8D19113856D78D1D93FEC6FEC6186214930D6F2B34DD338F19BB626C1798E262
              2CC0BB5201F1B9166AEC9ADA6F8885040F1D9B32B4B88038040999F3EF37FC81
              3D130A583A63259E9CF6108F8FB4B1526E6800BFB51EC4EF9DAB30AF199BBF69
              C62A7B508F22202ED0047728BA144177B511DC917626A9B2B6B0A8C01201CD6F
              C059EA36B827707CA28FE6855BD0D17B08FB4EBD86F30359B3F72D993ADC3765
              395E5DF6213EF86AFD730B365ED07BD7E185C449A3CC21070BB58ACFB658E788
              AF95B2627CA44C71313581112FADD6F1B8073FD54558D3F4260E9ED98C23ED9F
              A02797C5B627B4919EDC200EB77F8AEF5B376375D35A34DE9C797ECECB9825BB
              8D2060F6E7867107C1690148075392C82E9AE8AE08A35D2CA4F8CCE37C47A105
              CB67AEC489CE8FD13DD86E3CA5AA524FE6B27691CF7EEDFC088FCF5C81703C36
              C1465AD5714CC9B7B7489346E050FCC118F3874F39D368D04272DAE5250628B9
              00DFE6F2983B29831FCE9C9402C8D68BE750557F2B73C90AF1647BFF493C72E7
              A352C1C50269AFAA55B275E058AED65EB352DFDD0D0AE773474C52BC3BFFF2AA
              BF6DC9F0DAEB5F2B74E58E962B637099052A395943475C6934883C906FB5FDC4
              98ED39DF2DB495214CEB52F197DC38A3CBE655CA68355EEF501758A9F1D6770A
              EC4331C4B0D9BAC0B27F69AF92431452A5A5B3EB1BEAA8609A3D3CC719B169AD
              52BE96CE6CC2C56E868E6FDBC74C680A66E5927926692D79969977A341FC62B2
              1EE604D6FD4BDED9DD207DBBBEA68F109EF54E9AC7C2121E407B30758A39A551
              2C49551CBE04D44F5A089E63F89371DEF133B64A7C8A211A2977DD3BFFD959C5
              287FCDDF404A2BC9C8F8B6D93B9F9E744734F7E107AC7922BA202AD9777C37C9
              37BAE6D051E0FC197CB17F0B5EE44AA74A5A9806FB2902E73A3FC0648F71735E
              C1FA09B763F1DDD381C993EDB926579164BABA8053A769FE76EC3AF01ED672B9
              55BE90D4A87EE47A08940F5251E2D6E98F61F6B407B13AB809332A19C4DD0B97
              70A2ED30B69FDE871FB9D241E983AD2437EE0338B1E278CA444AA69CD9C9C133
              40B9406108225B3E8C6E2481F27E7EF2051C54ED2FB62850A4CA45D5D5E51F01
              060083FBF06EB5D4FB060000000049454E44AE426082}
          end>
      end
      item
        Name = 'sprite_add'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC300000EC301C76FA8640000001874455874536F667477
              617265005061696E742E4E455420352E312E3162B5520C000000B66558496649
              492A000800000005001A010500010000004A0000001B01050001000000520000
              0028010300010000000200000031010200100000005A00000069870400010000
              006A00000000000000600000000100000060000000010000005061696E742E4E
              455420352E312E3100030000900700040000003032333001A003000100000001
              00000005A0040001000000940000000000000002000100020004000000523938
              00020007000400000030313030000000001B74D394D408860B00000899494441
              5458479D570B5055C719FECEB92FE4E20511444584F8A84A04341410EE056D26
              AF3131A6DAB4496AD24E8C63526BB0633B1D53671C1D9DD8E6514D4693B4DAB1
              497C549D2854512452236FAD4E24888F9811B8524185C205EFEB9C7B4EBF3D17
              5327A260FE999DDDB3FBEFFFFFFB3FBEDD2361F024399DCEA74C26D347BAAE8F
              EA9B8324496D8AA2CCABA9A9A9E5A71E9EED9FB84FF0F77D8569B00698F3F3F3
              F76A9A3E37100C4009AAD0740DB22CC36AB1C066B342D3B485D5D5D5DBC8AB85
              B7DC49FD19301892B2B3B3E7399D2E3D63DA437AD1812394F37FFA64C71E7DDA
              F44CDDE572E9E42B10FCE16D7712D9FB46F7471105050581CCAC1CBDA8A49C32
              3A75BDF4093D54946DF4823EDDB54FCFCA9E4123F22BC96F0D6FBB93FA336040
              7F242525252727A734C114818A63C5D0760E8112E082D84979561B87CFAB9896
              E98423CA868AE3C763B8D22DF67E978401DF0D81DCD7DF8DE4D8D8D8A9C2F08C
              E9D9C0F957A0457036865A6338606F7CB7FC8E8117073784DFD503FDD1400648
              67481293ADBEFE2CD0B51DA6681B24BB1988341BBDCC6F5CD90593CCEFB00103
              7AF5761AC80091D1AA2C41F1DDF4605FCD0390E24DB0C4C8303B64A317DFDB8E
              0D65359049554E93FFBE326D200384B0607B7BDB729B55C7EA1DE3B1AF6234A4
              D13A4CA318CF441DDB0E27E3BDFD636135EBB8D6DEF667C16FEC1C240DC65D22
              CA6399E1271415D101459CD4C429096693042B236EB368B871BD6DE5F9F3E73E
              E5423B31238BBDB5A2A2A29CFDB71EF93E492828949B9BBB8268173D69D2444C
              99321E9ADA0D93E44184D58F088B029FD7B3BFB7B7A7262727673E95D752C971
              82D466EE1D302107F280949E9E3ED96E8F6A8C898D43C981223AF802C54E3216
              53A766C01E69A3274CC631B5508888C8F0F0DB6AB5A0B3B333BDB1B1B1814B86
              17FAF3C040065888FFE55E5FC0B5B7A814E3E44AA8DBE71ABBCC8FBF89C3D77F
              8413D5FF82DBDD2CA4232D3D033367CEA4477C58BAF43501D3C584E79F508E22
              847D1F031C794E6777746C024A8A3F86FA7E1442AC4041A6A878985FBC16FEB8
              9DB4AB0C6C24F267CD871E0AA2AAB2229AB31EB174BF3920656666CE56550D4F
              CEE121AA7E097D08676D26486C7AE03AD48F2422631C50E2040EB9806D14FEB7
              D140C372CC9FFF53C32B797979EBB84B646DBF742F032C66B33937442498F283
              64E09BBDD0AD54609121DB2458A21886611460EE006E5603BD55F0A8323EBF12
              87D985F5D8B9E313C82643FC18B6BB26E3BD4260CFCB739679837AEECEB77F8E
              C9FF5982A06EE10E969EAC60D9BE49286A1885081B41898A846759951C139465
              5AAD29975B5BDD6F3537371FA5AC2B6CDEFB0D81887674489330C67E051A7587
              3D40D9B28EDFACF918B3F2D26009FD177693170E5B10434CDE26CDDFB5FFE2F9
              AF5EA8AEAE7C8ECA4B29A39D4D5C5FFDD2BD3C109BE7747584243B6A3F9B07B5
              72314212719F248702B0CC75D3C431387DE61C962EE19A1A14A73B535B5BFBF2
              B41790149F8ADF4A16B8786883C4C1250DC7343F5694AD461DA78C95BB196066
              F21CF507D482D797AFC22F266F40D07D14BA1C3680EE85A4AAB04E5C08A46D41
              3004BCB46001BEB974118EEC666F5C6A6FE463D39EC58363B389922273E902C5
              87B32D2770E4CB3DE8F678B794BE8157391DEACF00135F37BB15459D173D6C04
              4A0F15412B1B0A55A552DE78BC188D72D23515BA38B5C902CBCC2FA05AB3F0CC
              CA14C48D0FE057B3D7C2DD5585AFDA3E437BEF4D436842941D6923E72129C689
              CD252BD176FDC6D6D23F60F1ED06483366CCC862E6FF95B09B2EC956141D28C7
              88C066280D8590CC913033FE975A239112EF87D946D423BC846898CE4BA271F4
              9B585FB90E854FAF4655CB06B4F7B8115081F79E0AC7E0F503126CCCAA84A149
              708E5D868DC5ABD076B977A644EC1648F510E3B780A74EF2F9FD98387132DEDF
              B41509B157A11C1B479F44C0C2DA3F7B390A3F5E3F1DB1510A163D7A052F3FD2
              4AC334787B15BC7156C1F49C85B829D5C0ED693422ECA5811B9F0C1B50785042
              240F20829EE448855DCFC58EF2AD5532717B0FA757F87CFEA4E89858BCF3C755
              D8FD8FED4818D60AA5268DC0638525D2048FDF82459B1EA4F220CB4DD73E383C
              0679BFCF46A3DB01C562C679E6F9A8783BDC3D8D50A933C04A0CDEF63E166331
              27D6048FE095CC70CA8140E0F310D1E6D5D77E8D4325FFC4C38F3E0DB4AE44B0
              760219542A2786F07259B431954F7182BABFBBA8BAAA7C8E19BE2F45663FB73E
              0D87FF1D676473BBEFA491DA6F3DA6E3DD27747C30277C7A41622CE6C49A9815
              BC628FDCD4D4F4AE8083B223BCE9BA0BA19DE189DAD6C31CC598475BD0A358F1
              B3B553D1D4C66CD602674E9F3EB586FB2ED6D555BFD2D57975FDD0C810D6FC7D
              9C21AC37D8C2A719070390E011BC628F68292E57C1859E9B92B5F22FA71015CD
              9A9209DD3CF8D61D49D876702414512C545E575BC5BA03AF3EF4B045B2250C1F
              3E3CED817153768F78B612F9BC127875B0E4E829F67E26E186C7C35E58562A21
              824948246769B2CED957548591B0B7A7C7B3C9C6242BAE4EC425772C366E4F81
              EBF92C7CB86F344B4E42C0D7B5AB4F39D1075D6C02D9C4D3BBA5A3A3E3548FE7
              C6167F5B143A3AC3C2F944005FE810D1BB45626CCCB1091EC1AB78715A7820D2
              E170A46664649E0CAA1204F432C960E61B2F18F0563634D4AFF3F97C02CBDBD8
              84729EEB5B32F6B34DFDE1C3138A939EB934C295C302E0AC4A470A0FAC72853D
              B0BA32EC01339D4BF1A824165E28C34B4280B82A47B21CEB64D994E8F707EA3D
              9EAE23E7CE9D2BE1BC5078BDAFF7B151EC1D24BC382A3131F1C509B37D6B13A6
              779A72C58B90B3840786CFE081855A582C0C25507312B8D684E2637F42A13040
              90F89BE19D0BF178F0B30985E21121604C28BEFDD4FD9178B8123090EA5C8A25
              0913308BCF472424F0C4422989C88D765E4B17BEA6FBDD38F8C5DB58C1E9E65B
              06088810AE14BD50268C10CF6BDA3B28BA158AE16CF1131E414EF20C2CB63A90
              1EBE7248E4087A50DF52870FBF2E83F8876C05D0FD3FEE7781007D2886600000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'object_add'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC300000EC301C76FA8640000001874455874536F667477
              617265005061696E742E4E455420352E312E3162B5520C000000B66558496649
              492A000800000005001A010500010000004A0000001B01050001000000520000
              0028010300010000000200000031010200100000005A00000069870400010000
              006A00000000000000600000000100000060000000010000005061696E742E4E
              455420352E312E3100030000900700040000003032333001A003000100000001
              00000005A0040001000000940000000000000002000100020004000000523938
              00020007000400000030313030000000001B74D394D408860B000005B0494441
              545847C5566B6C145514FE76661F7D42A9408B0F2C04536D7CFC3080A6206A0D
              D6079110090989CF18C018230623F2831F86F82012820F0236311A3126065349
              10C1283EA88896F8C047B5026DA52A5D49DBA52DDD9D9D9D19BF7367673AADDB
              425712CFE6CCDC3DE7DC73BE7BCEBDE74EC8711CFC9FA4008442A1ECDF6114FD
              6CE31C834A0E05644E9B31283B87FE6F5CDB1CE39FB4128FA0D100443FDE70B5
              517E692D0A8B8AB3A2FC283978063DBF1FC42DEB7FC809221780E8BEF5971B15
              D57528292D454FEBE7A365E8AC24BECBAB1760A0BF1FF1D6FDA8DFF0EBBF408C
              04107DFFA919C6F4ABEE40C98489E83D7600214DA758F4E305212570E0D81626
              CDBA01037DA771E2C73DB8F3F9F661208200A2BB564F3366CE5982B2896548B4
              3551CBE0D4C92F1F6278B507E058289B391F89D309B4353762F196933E080F40
              78C78ACAC6DB1F7B7D512CA6C356FB27FFC023C903A2D19D6158F8E0C50776DF
              D3D0B584AA8C07A0F49D55157D37AD7A152D8DEB98F6B002C08772F0DFC905E0
              D819D42C790E9F6E5F8965DBE313A8E8D75C03C454A6982A3D56887041B1E248
              41D17961CF9FF89618124B62CAC303A0291911EA9AA638ACEB0887C3889C0716
              5F9E5F89E1C677637B2598FAF68ACAF8CD2B36A163FFCBD0C25165FC537BB75F
              BFECA4732655402923F9CAAA0B60D93663A75155F7283E697802CB1BBA2A68F2
              378BED924A8B95E1C6D7B90734C50E2CD4D55E03DBB2F302A0EB1ADEDD7B089A
              3E15B6C8E85B62644BA0C82B812BE49995956B8A09846AD33491164E8F9339C7
              3433595F2EBB25F0F780221F80ED10B39D568DC7CF00D3E764983ACBCA83398F
              C1E44479FE5453630C152B4B4319500F9BE9CA22E65B265974E23A1B2FBBF386
              32A02B9F122358CEE12570780AB86ACD63760E9B0A99A2DE79704816445F3A17
              2DBE2506C53E0D07C023E296205B06B662598D239B50DEE3642985EE97C0F5AB
              8E612E00921787E854AA3841368C1C23554F71365ECE964D820737B6C408D620
              9001A69C5D4A52E622A68A19C8B5B2B1580077183DD836D08CC7137BB1F3A223
              78E4D46EACEEDD83AD941D4FB41358362869A80FC8831B479032BA7AAB0C305F
              5630676390C55B6C57FA171C2D4C60E1ECA5B877FA1CC422854A679849FC7CA2
              192F7DFF26CA2B9548EEF9E17BC0815B022F65920DB9CF73AD7424CB997F2B75
              047F4C4C63CDE2CD282BB3B1EFB727D1F0F5838A652C32D1256715A16E3D3631
              AC9C0B97E40AD6589F1077BEAC5C5876AF750E47D062DADB8C04BA8A535859BF
              0E073A9EC1579D3BD0933C836D77398A652C32D189CDE48A92E50BD6A0767806
              E82848720A72AD76249BA685FD4E1B6EBB7619BEFBEB35740F76222C951CEA37
              6A2C32D1898DD8C6CAF16C0000EB6D9B1C0DCD922CA8464496F7683C6898E8D4
              FB306D4A313AFB5B90E1620C6EB47460B3C95864A2131BB10D858319901E6199
              7E78DA9109C048216324F91E9D53C941352F9E3CACE6BDB0D0C1E67AA67E91FC
              7349C622139D48C556E6046E43F67D02900CA869AA65DAA859F6B4AAB10B2937
              9DEA4E20D4743F06D22702BB6A74121BB11500FEF7C0D6E517C7172FAD47B2AF
              4785929A51A9D2EF10CC58D4DD676043FA23CCAF658A25D55C87C9778A3D67CB
              AD2EF0D51F8650C0E546183C1671F743D3C1118DC86DC5EE095099E03BA48779
              8944CFCA95993274F7B8CE8BF8B155422E8ABABE8564AC6464B1115B7310DFFA
              00D485C10FB368341CE088CB9C3116171747310FD538DE2E170EBFEF1920C2D5
              52E5938C45263AB111DB3FBFC116AF045336DE7DC97B25D150ADC386307AB573
              53C672703A69A1B5AA17564D0AD7CFA6904B636F024FA8A208FB9E00904FA343
              878193C7B0AF69331EF6009452359D3C99EC6FCC7190D44C7A6EC575ABF0D085
              57606EF565FCC3AF3E7E932ACA104C3C0EB41E05BA8EE2C097AF602DC52D1E00
              311307056471960F496F97854CAB9A8FB933E6E1BE8249A8F1D349AFA95EB474
              7C8137DA9BD044491B80EE7F00A2130EA99FEA4F1E0000000049454E44AE4260
              82}
          end>
      end
      item
        Name = 'tile_add'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC300000EC301C76FA8640000001874455874536F667477
              617265005061696E742E4E455420352E312E3162B5520C000000B66558496649
              492A000800000005001A010500010000004A0000001B01050001000000520000
              0028010300010000000200000031010200100000005A00000069870400010000
              006A00000000000000600000000100000060000000010000005061696E742E4E
              455420352E312E3100030000900700040000003032333001A003000100000001
              00000005A0040001000000940000000000000002000100020004000000523938
              00020007000400000030313030000000001B74D394D408860B00000586494441
              545847C5576D885465183D77E6CEC77E59A2AB69A189C4962154621A16048698
              4BB8592A4A590495F4CB3045D3FE2991C2D60F53098A522914C92D5831622BAA
              AD55A9C0C8D258D45DDA585BBF57F763E6DEB773DEB9776767F6CEEE82446738
              CCBDCFF3BCF73DCFF37EDDEB1863F07FC20A701CC7DDF6091A1047ADF1014972
              72FE02847627467A685CB70275BCCD92EEAA3DAD0D26E6D6FA4A68B89CF88098
              E3C0F1B38D7B564DAF0B05546D3B80AB4BE73531800A468289E160F37CAC5B86
              31BCBB46563DBBEFDCD5350BA700A3680E26F0CE9136EC7D66EA183730A5253C
              E375E3A7536F53508C4287D6C0E8C712CDAA79157E2ECB3429016965DE9B013E
              FBD33E3F57AA62B08DF42DBE8BFFEA90ED6C2CE1C8694C3F928972A412154826
              87D2DAE9575C80B01BFB9FE133927120C5B4D211945D7EC505D068E6E1C34322
              5E86844BEABF98815D71C590822CD3530709914F1E42DAE5575CA89CE641F033
              48BA6906A64A527EC545C1E383C3CEDC08863EC585E06D1E8699B9ECC07553C3
              306DE3A2A0E510679963CC321E416BA75F71210A04501BCB4C0171919D0D21AB
              A30A48407E1C07A0CCC24C8BB31F6C2F5901C731B693E8CE43A66D5C143C9A4B
              751ED20EC1A0E6BCCDC3707A4597BD908A8B82ACA31130B8356FF388C7629C64
              E5B9D95E82F22BAE189AD57AB0CB711E898A1BB20AB420531CDF8AF47854A64A
              537EC5156BE06E6A275A798A4C0E43FA15A778DB2ED88A27BCB51FADC641A536
              A8E811CE41CDD43666D0BD7E39A6F3F63C59BD6CE7F143A95BAAE7E92C19094A
              B6EFCA3FCD075E99FD6428E056DAA79163E557D00890C64BE419F2325945F220
              C078920B6D44682576916DA180046F2A481669D4D07E7C9DD4AEA44ECB48ADD1
              D126D04BF6705F1FAEE0FF3DC20AB8DD9B963624E1D75251E01A069C041998C6
              8AAD9F0EBC0F7CB8ADAF816BA87694CDB912FA1B9F5F9FAA0BC7AB4C9D2796BF
              C44BCE90608646C2F6E0C3D9BFBB96172ABB8EE33275FED812BA794EB7761DC5
              C1931BF1C7856F06F2D123EF1EF7289E9EF126A657CF41D3A1A46D1F0AD0060F
              D3DF0BD3F4416EC32E052F0B67FE0B8190FCFB806EFB7A3DECF87235DA131F63
              C17D4BB162CABB3CC2A591BE4C0F7E6B3B861D3FCFC7CCB12B7187B75B669DD2
              163665E367E1A7391763344715C1269F458C0C1046391E85ED3AF614BA2A7EC0
              DA45F568BFDC8C23A7D7A3B35BF3149858598199B72DC1DABA7AEC3CBC191DB9
              04B439E6E17B19F8490E86652A82818F714570CE7BCD3877E32BBCBC7023BE3D
              BB152DED7B71B1E73A762D3696BA964D3EC55C1CB31FF7AFC48305028CDF1F74
              92809F88A0ECF42BAEE895CDFD35B6098FCF5A8E5F3ADEC7851BED36B5C15349
              D7B2C9A718C58EABC1EB8515301C0297025C765492F433AE08655D6E33265557
              A0FDDA4964351FB823F60FDA15752D9B7C8A512C0FD6E20A7830CA3021262248
              BBADC09017928492EDEC396EA7C9F60506F50B59FA27EC385BE85A36F96455AC
              DA0C0850493DFEA2B32EA4E28A60ABDDDDDFC6933267180E8A516C8100C13314
              A039C06C4B927EC515430AAEF4FEA50D056F7CED60439383355FA88B1C742D9B
              7C8A51ACDA1408F079C479A9343B895A01395A3FE38A60AA7A1EC0858B3CD279
              AAE8C8AD0C8EE510BAB63652318AEDBB86137901949375390C65E5C80E43EB67
              5CD11B7D66EAD53568E5D918A78B8B852F2FB98E42E85A36F914A3D873CD782F
              3C0B26DCD8BCAC35614C250D4193D23014EB39A63BBDE560F83E70FBF60DA74F
              9F705F2BEF9BFC391E9A4D0BF565B85832C168D96F056D7B5C093F1EA7908E45
              D97D5B0ECF0D05DCECFB80DADD4BD6CC5D8D1727DF833935FCFC9A38916B3FD8
              6BB314D3D9099CE2A75BC7EF6869D98D7A9A5B42012AD6CDBC0FA8BD3E54C791
              93EE7C0473A63D8CE7D26331C34A159856EF259C3CF33D3E3AFB1D8ED2D206E0
              EF7F0195D054128A4404190000000049454E44AE426082}
          end>
      end
      item
        Name = 'tile_add_custom'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC300000EC301C76FA8640000001874455874536F667477
              617265005061696E742E4E455420352E312E3162B5520C000000B66558496649
              492A000800000005001A010500010000004A0000001B01050001000000520000
              0028010300010000000200000031010200100000005A00000069870400010000
              006A00000000000000600000000100000060000000010000005061696E742E4E
              455420352E312E3100030000900700040000003032333001A003000100000001
              00000005A0040001000000940000000000000002000100020004000000523938
              00020007000400000030313030000000001B74D394D408860B00000690494441
              545847C5560B6C1455143DB3BBDD5D5AEC22F22D3F493506C5C468A0946AC247
              3E6163A8D81A52BE09241A13C10421D8488C31A0A0C1A051894A4C6DC10F2D14
              C2122B05D1B2B420248882115BA0142A4D5BECBFBBDB76C77BDECC96D9EDB6C4
              04E34DEEE4BE77EF9B77DF9D77CE5C0D8063DB5728861D5E3D2C2311CD0619A2
              6ADDF39824437DF997D5C5BA0DDE7058577E9B4D83AEEBBE8265F76772DC91BB
              A8D8A1695E99547E681ABAA0FB9236EF53FE2FB6058BED707A2D6E8411F2ADDC
              E0CA74C8781037CFCE28918D655B113DDC8342FFBC54311345C3619BC3FBF2DC
              143898AE48B7BCE88323D7BD620EE2D8A9E95E7BD62A398A9B430908402BFCBC
              D76FD39CDED90B9938477C2170B4D8A9FC9C7233B3CE5003CE577DA494B67958
              A7E1D7D114040E561A4ADBAC06777443CC9ECE2604CBF294D236ABA1FCAC6C40
              D65CFAC550DA6635DC4C40EA493B084FD258A5B48D39F1191543505E3244CE43
              A5AD262DFE50770742F70E33546C4DB90CBF3264A7A4FB0CA56D8A61F2E9763A
              31CC93AA9476A45C144DB6E891D70C1D6C286D9B998112794120A11BA1E12394
              D28EDA45421DF2319347184A3BB29C77406F6F82BFD0BF34C37A4938471FC79D
              2DF5FEA2B2B0F8CDB24840A0A5A1D77FB33DE01F75A834C37A09FF9239B1D444
              4B7BADFFC7BD2919D64BCE393175E6718FE878D161A24C8822474083E83535FA
              0FFD4C8093BCADBC30666154E601D14E35FA0FFD2A813CC1A94D704A7850F8FD
              7BB4EE532BD7273CC9712037B3D881689CF7003ED796FD0AE73905D5C552D728
              9ED0C2F0ED5E364EF9B77D2D3C431E31978B9B44E0DBB018060F68B2F92C09B5
              E2B4F480234D4CF2806E1792B167AD9654790811C1392C38D764F33573C646F1
              C487DFD7DEF6CBE659313CB3D73F2F9A07FAE0D4A8868B7E9EBC2FCE959F19B9
              79F2589E302FACE117339667CC629A3CC08758F1704A25A6FBE2DCE297671F9E
              B0F88D64E3F38CDA8A2FE80FA74A246C209C931362794265650A3F6D2CCF4496
              F30EE8F170DA19BC75813E8E89F3D13138E79C586A829C505486189E68ECF5B7
              0DC0334C331E0FC82547A368B52897FD2F3C201F0A1D6A14DF7FF778E0DD6F70
              426A9166C5A968D5ABD9463FB024BFA64F3F2030F1ED593A41E13C98FBACFCEF
              11C513DDD20FB8B714F7F6038E189E613FB0C2EC0712B9F940FD8081F3FEFB01
              BB863E3CA1C7F403B3FAE90798808B89139B95370A55C00363B2ACFD80C234B1
              7DF2BA9AC3744192A51F50052537749F2B51B195135391E72EC3DCAD68E1BB0B
              0416BBF703135C333063E8DB487B2C4DE2D469DC4C200AA786DCC669E411C139
              25A61F30FCC20D41CF507CD6588A33978B307766369E1B3F15AE046351B0AB13
              17AE9DC68173B351753E07E3C23B39ADA95B49D845704A19A81FA0C4EB07DAB4
              20DE6F2E41ADBB1EEB166C474D931FDF5DDA80BAB67615327270121E1DB508EB
              32B7E3E3C3AFE3A6715FEC4C406F154CEE159C9A7744FE1B52E22EB0E02A2AD0
              52E7DF57D61585632BCE6FB485FCF5BEA28CCB636BB076FE9BF8E9EA66D4B5D6
              4855804F161A8BD61CD25051938F2B4DC7F1C2FCD7B0E3E01B787C09A6F018F1
              7880B9DC12BD6ADA77C279EACC5CE4AF7866D5E476AD1C352D17556A1D5DC00E
              AF91C05A9F86C4043164C771C90F23494F47C1915D153C2CB1CA17C92AFC6AEA
              6FA2DC9C3C10CF4F9B73F451EB9D1E4C1E3D3C0935AD17154A784F4291928AD0
              E61C7D8C61ACDD8569AC4042D7A6C5F55A4F8F27F20B5497C2AE353BDEFA7638
              87F9EF85EB058C1EABDBA6E9CD4BD6DB947FD32E34FCDC80E49C05E9B870B31C
              EF3C6D9CBA3FD958AAE19151E9D873B85C7DEE243DDCEDB167AF843DE72543C5
              D6C35D1EFAA8615DF3B05F989365286DCE45FCD27C24F3246DA16BB0F38D7710
              C630966B18EE2483F5D3D793079C3C796CBF60E109274379319B033730486636
              FDA061E3510DAF94700B4368738E3EC630966B7AF3EDA7AFEF15963DAA5FB056
              594247BAC7A351AEAD4B2E5AA2B431834513158D19425BCD893286B1C1569C57
              096802FA7FDBD75B79C2212FCC18B3005557142DC329E304C10B378A086DCED1
              C718C656FBF1A9E281DAF6A03FC5772CEA7FDF11D67B79A059FA85E3EC176EBB
              7BFB7A8E43ED3859D9B6737A422B70EA2C903E4536911333C92DE5122CC20A30
              0182BAFC0CD056FFC4ADCA636795F76EF0C00451C6A44C7B11AB532621EDA107
              E5B38C9405E68A6E59515707FCF12750FB3B2A2A7662AB4C9F66020C89F7BF0E
              89920768C7F3C7FEEF898864D1D1139FC254D1E5AE21986CD448445606FEC6C5
              2B279077B50C1532238743DD3F63027E885CC5294C0000000049454E44AE4260
              82}
          end>
      end>
    Left = 360
    Top = 184
  end
  object vilToolbar: TVirtualImageList
    Images = <
      item
        CollectionIndex = 0
        CollectionName = 'asterisk_orange'
        Name = 'asterisk_orange'
      end
      item
        CollectionIndex = 1
        CollectionName = 'folder'
        Name = 'folder'
      end
      item
        CollectionIndex = 2
        CollectionName = 'disk'
        Name = 'disk'
      end
      item
        CollectionIndex = 3
        CollectionName = 'arrow_undo'
        Name = 'arrow_undo'
      end
      item
        CollectionIndex = 4
        CollectionName = 'arrow_redo'
        Name = 'arrow_redo'
      end
      item
        CollectionIndex = 5
        CollectionName = 'page_white_copy'
        Name = 'page_white_copy'
      end
      item
        CollectionIndex = 6
        CollectionName = 'cut'
        Name = 'cut'
      end
      item
        CollectionIndex = 7
        CollectionName = 'paste_plain'
        Name = 'paste_plain'
      end
      item
        CollectionIndex = 8
        CollectionName = 'cross'
        Name = 'cross'
      end
      item
        CollectionIndex = 9
        CollectionName = 'find'
        Name = 'find'
      end
      item
        CollectionIndex = 10
        CollectionName = 'text_replace'
        Name = 'text_replace'
      end
      item
        CollectionIndex = 11
        CollectionName = 'zoom_in'
        Name = 'zoom_in'
      end
      item
        CollectionIndex = 12
        CollectionName = 'zoom_out'
        Name = 'zoom_out'
      end
      item
        CollectionIndex = 13
        CollectionName = 'zoom_actual'
        Name = 'zoom_actual'
      end
      item
        CollectionIndex = 14
        CollectionName = 'control_play_blue'
        Name = 'control_play_blue'
      end
      item
        CollectionIndex = 15
        CollectionName = 'help'
        Name = 'help'
      end
      item
        CollectionIndex = 16
        CollectionName = 'cog'
        Name = 'cog'
      end
      item
        CollectionIndex = 17
        CollectionName = 'image_add'
        Name = 'image_add'
      end
      item
        CollectionIndex = 18
        CollectionName = 'sprite_add'
        Name = 'sprite_add'
      end
      item
        CollectionIndex = 19
        CollectionName = 'object_add'
        Name = 'object_add'
      end
      item
        CollectionIndex = 20
        CollectionName = 'tile_add'
        Name = 'tile_add'
      end
      item
        CollectionIndex = 21
        CollectionName = 'tile_add_custom'
        Name = 'tile_add_custom'
      end>
    ImageCollection = icToolbar
    Width = 24
    Height = 24
    Left = 360
    Top = 256
  end
  object icProject: TImageCollection
    Images = <
      item
        Name = 'tv expand'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D49484452000000100000001008060000001FF3FF
              61000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC300000EC301C76FA8640000001874455874536F667477
              617265007061696E742E6E657420342E312E35644758520000009D4944415438
              4F63B029DBFC9F580C040CE878101880CCC9CCCC0452A80A0861140ED906D4D4
              D4FCAF6D6CF8EFB9A6154C83F83005D8BC02C32079B02290A6FBEF5E800DB8FF
              FE05D81090380863D308C32079B022CFB5ADFFD1715A5A1A1863D308C37003D0
              5D50554BA2171A1A1A50C200C407891383B10A9282C14475136E1760733A0C83
              E4C18ACADA106170E3F5E30188058A5D802F0CF0E3FF0C00625DB3797ECFF19B
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'tv collapse'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D49484452000000100000001008060000001FF3FF
              61000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC300000EC301C76FA8640000001874455874536F667477
              617265007061696E742E6E657420342E312E35644758520000006E4944415438
              4F63B029DBFC9F580C040CE878101880CCC9CCCC0452A80A0861140ED9063434
              34FC47C73005D8BC02C32079B801F7DFBF8063920D38E3A1FF1F1DA7A5A58131
              368D300C378062178034A06390383118AB2029184CE0730136A7C330481E6E00
              4561309463E13F030043F9B6C2AACD20DB0000000049454E44AE426082}
          end>
      end
      item
        Name = 'tv showlines'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D49484452000000100000001008060000001FF3FF
              61000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC300000EC301C76FA8640000001874455874536F667477
              617265007061696E742E6E657420342E312E35644758520000008A4944415438
              4FCD91CD0D80200C8519CC794858808B98540F2EE480481B4B8054FEBCF8928F
              A6501E05D4622FDF4B902AF981419A186342C80B5A64C9B48173CE9770817415
              06D7A341AA6D070CF306986BAD09692313F46E10D4DF010064F74F0D5A889323
              D0B01E400F879D70E402A97506D7A9C89EB4216AF8179E13A3301FFA85CF1DD4
              DEA08E57372EBEC4A2D5CACC830000000049454E44AE426082}
          end>
      end
      item
        Name = 'tv hidelines'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D49484452000000100000001008060000001FF3FF
              61000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC300000EC301C76FA8640000001874455874536F667477
              617265007061696E742E6E657420342E312E3564475852000000644944415438
              4FCDCF410AC0200C44D11CCC73F5623DA06D020361F80B0B222DBC8DC9171BE3
              BAE7AAF70BF7830BE8F08B0D37D06143BF22B5E381A3506AC70347A1D48E078E
              42A91D0F8EC3C38E9E2E39C7A8A350728E5147A1E41CA38E42C93946EB663C73
              DBC7EE5CC6F5890000000049454E44AE426082}
          end>
      end
      item
        Name = 'tv showfolders'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D49484452000000100000001008060000001FF3FF
              61000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC300000EC301C76FA8640000001874455874536F667477
              617265007061696E742E6E657420342E312E3564475852000001024944415438
              4FCD51490AC24010CC93041144CD77027980B91861F4E04DD4E8273C8BF80AE3
              727401F1012A7810115376B7266482C678B3A1A6E9999AEACDA8382364059991
              C41F08C403DBB6C9E9846FD0827702F341A5430023F9C690C3755D241112965E
              01B86F80DB0AD3761E7EAF28622CAC09C4ADDE50EC9E02DD1C70F1111CC6C075
              4D425BBADE4715BD15E0D8B22CC1A29B07CE13DC778E20D855816085995762EA
              670132795BF4CB9479089CA8E223E1D4A6EB2555600A47484A29ADFFB800F73A
              EB9BD43BC13329B3299FB519A48189DC6FD8731272D49A4A06C795843E2464DA
              82D3920F91FDBC8557C6C838FE690B691564DA42DA0CB8D7CF5B80F100235EE8
              D4D50AC9970000000049454E44AE426082}
          end>
      end>
    InterpolationMode = icIMModeNearestNeighbor
    Left = 256
    Top = 184
  end
  object vilProject: TVirtualImageList
    Images = <
      item
        CollectionIndex = 0
        CollectionName = 'tv expand'
        Name = 'tv expand'
      end
      item
        CollectionIndex = 1
        CollectionName = 'tv collapse'
        Name = 'tv collapse'
      end
      item
        CollectionIndex = 2
        CollectionName = 'tv showlines'
        Name = 'tv showlines'
      end
      item
        CollectionIndex = 3
        CollectionName = 'tv hidelines'
        Name = 'tv hidelines'
      end
      item
        CollectionIndex = 4
        CollectionName = 'tv showfolders'
        Name = 'tv showfolders'
      end>
    ImageCollection = icProject
    Left = 256
    Top = 256
  end
end
