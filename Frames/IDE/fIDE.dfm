object frmIDE: TfrmIDE
  Left = 0
  Top = 0
  Width = 800
  Height = 600
  Align = alClient
  Constraints.MinHeight = 600
  Constraints.MinWidth = 800
  TabOrder = 0
  object dsIDE: TLMDDockSite
    Left = 0
    Top = 33
    Width = 800
    Height = 567
    Manager = DockManager
    Align = alClient
    TabOrder = 0
    Layout = {
      EFBBBF3C3F786D6C2076657273696F6E3D22312E302220656E636F64696E673D
      227574662D38223F3E0D0A3C736974656C6973743E0D0A093C73697465206470
      693D223936222069643D2253454C465F53495445223E0D0A09093C7A6F6E6520
      6B696E643D22484F525A223E0D0A0909093C7A6F6E65206B696E643D22564552
      54222073697A653D2235363422206473697A653D22302E373231323237363231
      343833333736223E0D0A090909093C7A6F6E65206B696E643D22544142532220
      73697A653D2233343522206473697A653D22302E363238343135333030353436
      3434382220697373706163653D2231223E0D0A09090909093C7A6F6E65206B69
      6E643D2250414E454C222069643D224C4D44446F636B50616E656C3222207669
      7369626C653D2230222F3E0D0A090909093C2F7A6F6E653E0D0A090909093C7A
      6F6E65206B696E643D225441425322206163746976657461623D223122207369
      7A653D2232303422206473697A653D22302E3337313538343639393435333535
      32223E0D0A09090909093C7A6F6E65206B696E643D2250414E454C222069643D
      226470456469746F724B657973222076697369626C653D2231222F3E0D0A0909
      0909093C7A6F6E65206B696E643D2250414E454C222069643D2264704275696C
      64222076697369626C653D2231222F3E0D0A09090909093C7A6F6E65206B696E
      643D2250414E454C222069643D2264704D65737361676573222076697369626C
      653D2231222F3E0D0A09090909093C7A6F6E65206B696E643D2250414E454C22
      2069643D226470536561726368526573756C7473222076697369626C653D2231
      222F3E0D0A09090909093C7A6F6E65206B696E643D2250414E454C222069643D
      226470546F646F222076697369626C653D2231222F3E0D0A090909093C2F7A6F
      6E653E0D0A0909093C2F7A6F6E653E0D0A0909093C7A6F6E65206B696E643D22
      56455254222073697A653D2232313822206473697A653D22302E323738373732
      333738353136363234223E0D0A090909093C7A6F6E65206B696E643D2250414E
      454C222069643D22647050726F6A656374222076697369626C653D2231222073
      697A653D2232373322206473697A653D22302E34393737393038363839323438
      39222F3E0D0A090909093C7A6F6E65206B696E643D2250414E454C222069643D
      22647050726F70657274696573222076697369626C653D2231222073697A653D
      2232373622206473697A653D22302E3530323230393133313037353131222F3E
      0D0A0909093C2F7A6F6E653E0D0A09093C2F7A6F6E653E0D0A093C2F73697465
      3E0D0A3C2F736974656C6973743E}
    object dpBuild: TLMDDockPanel
      Left = 6
      Top = 357
      Width = 564
      Height = 183
      ParentBackground = False
      TabOrder = 8
      Caption = 'Build'
      object tvBuild: TElXTree
        Left = 0
        Top = 21
        Width = 564
        Height = 162
        Cursor = crArrow
        Hint = ''
        PlusPosition = vaMiddle
        BorderColorWindow = clWindow
        UseThemeForSelection = True
        ActiveBorderType = fbtFlat
        Align = alClient
        AutoExpand = True
        Style.TextColor = clBtnText
        Style.FontSize = 8
        Style.FontStyles = []
        Style.FontName = 'Tahoma'
        CustomPlusMinus = True
        DoInplaceEdit = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBtnText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
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
          E6010000424DE60100000000000036000000280000000C0000000C0000000100
          180000000000B0010000C40E0000C40E000000000000000000008000FF8000FF
          8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000
          FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF80
          00FF8000FF8000FF8000FF8000FF8000FF8000FFC0C0C08000FF8000FF8000FF
          8000FF8000FF8000FF8000FF8000FF8000FF8000FFC0C0C0C0C0C0C0C0C08000
          FF8000FF8000FF8000FF8000FF8000FF8000FF8000FFC0C0C0C0C0C08000FFC0
          C0C0C0C0C08000FF8000FF8000FF8000FF8000FF8000FFC0C0C0C0C0C08000FF
          8000FF8000FFC0C0C0C0C0C08000FF8000FF8000FF8000FFC0C0C0C0C0C08000
          FF8000FF8000FF8000FF8000FFC0C0C0C0C0C08000FF8000FFC0C0C0C0C0C080
          00FF8000FF8000FF8000FF8000FF8000FF8000FFC0C0C0C0C0C08000FFC0C0C0
          8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FFC0C0C08000
          FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF80
          00FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF
          8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000
          FF8000FF8000FF8000FF}
        MultiSelect = False
        ParentFont = False
        ParentShowHint = False
        PlusMinusTransparent = True
        PlusPicture.Data = {
          E6010000424DE60100000000000036000000280000000C0000000C0000000100
          180000000000B0010000C40E0000C40E000000000000000000008000FF8000FF
          8000FFC0C0C0C0C0C08000FF8000FF8000FF8000FF8000FF8000FF8000FF8000
          FF8000FF8000FF8000FFC0C0C0C0C0C08000FF8000FF8000FF8000FF8000FF80
          00FF8000FF8000FF8000FF8000FF8000FFC0C0C0C0C0C08000FF8000FF8000FF
          8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FFC0C0C0C0C0C08000
          FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FFC0
          C0C0C0C0C08000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF
          8000FF8000FFC0C0C0C0C0C08000FF8000FF8000FF8000FF8000FF8000FF8000
          FF8000FF8000FFC0C0C0C0C0C08000FF8000FF8000FF8000FF8000FF8000FF80
          00FF8000FF8000FFC0C0C0C0C0C08000FF8000FF8000FF8000FF8000FF8000FF
          8000FF8000FF8000FFC0C0C0C0C0C08000FF8000FF8000FF8000FF8000FF8000
          FF8000FF8000FF8000FFC0C0C0C0C0C08000FF8000FF8000FF8000FF8000FF80
          00FF8000FF8000FF8000FFC0C0C0C0C0C08000FF8000FF8000FF8000FF8000FF
          8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000FF8000
          FF8000FF8000FF8000FF}
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
        TextColor = clBtnText
        BackGroundColor = clBtnFace
        FixedTopRowNum = 0
        FixedBottomRowNum = 0
        FixedColNum = 1
        GutterWidth = 0
      end
    end
    object dpEditorKeys: TLMDDockPanel
      Left = 6
      Top = 357
      Width = 564
      Height = 183
      ParentBackground = False
      TabOrder = 11
      Caption = 'Editor Keys'
      object mbKeys: TMemo
        Left = 0
        Top = 21
        Width = 564
        Height = 162
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
      Top = 357
      Width = 564
      Height = 183
      ParentBackground = False
      TabOrder = 5
      Caption = 'Messages'
      object memMessages: TMemo
        Left = 0
        Top = 21
        Width = 564
        Height = 162
        Align = alClient
        Lines.Strings = (
          '')
        TabOrder = 0
      end
    end
    object dpProject: TLMDDockPanel
      Left = 576
      Top = 6
      Width = 218
      Height = 273
      Buttons = [pbPin, pbMaximize]
      ParentBackground = False
      TabOrder = 6
      Caption = 'Project'
      object Panel1: TPanel
        Left = 0
        Top = 21
        Width = 218
        Height = 252
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
          Width = 216
          Height = 26
          AutoSize = True
          ButtonHeight = 24
          ButtonWidth = 24
          Constraints.MaxHeight = 26
          Constraints.MinHeight = 26
          DrawingStyle = dsGradient
          Images = imgProject
          TabOrder = 0
          object tbnProjectCollapseAll: TToolButton
            Left = 0
            Top = 0
            Hint = 'Collapse All'
            Caption = 'tbnProjectCollapseAll'
            ImageIndex = 1
            ParentShowHint = False
            ShowHint = True
            OnClick = tbnProjectCollapseAllClick
          end
          object tbnProjectShowFolders: TToolButton
            Left = 24
            Top = 0
            Hint = 'Show Folders'
            ImageIndex = 4
            ParentShowHint = False
            ShowHint = True
            OnClick = tbnProjectShowFoldersClick
          end
          object tbnProjectExpandAll: TToolButton
            Left = 48
            Top = 0
            Hint = 'Expand All'
            ImageIndex = 0
            ParentShowHint = False
            ShowHint = True
            OnClick = tbnProjectExpandAllClick
          end
          object tbnProjectZ1: TToolButton
            Left = 72
            Top = 0
            Width = 8
            Caption = 'tbnProjectZ1'
            ImageIndex = 2
            Style = tbsSeparator
          end
          object tbnProjectShowLines: TToolButton
            Left = 80
            Top = 0
            Hint = 'Show Lines'
            Grouped = True
            ImageIndex = 2
            ParentShowHint = False
            ShowHint = True
            Style = tbsCheck
            OnClick = tbnProjectShowLinesClick
          end
          object tbnProjectHideLines: TToolButton
            Left = 104
            Top = 0
            Hint = 'Hide Lines'
            Grouped = True
            ImageIndex = 3
            ParentShowHint = False
            ShowHint = True
            Style = tbsCheck
            OnClick = tbnProjectHideLinesClick
          end
        end
        object tvProject: TElXTree
          Left = 1
          Top = 27
          Width = 216
          Height = 224
          Hint = ''
          PlusPosition = vaMiddle
          BorderColorWindow = clWindow
          ActiveBorderType = fbtNone
          Align = alClient
          Style.ParentColors = False
          Style.FontSize = 8
          Style.FontStyles = []
          Style.FontName = 'Tahoma'
          DoInplaceEdit = False
          Flat = True
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
          Images = imgProjectNodes
          ItemIndent = 18
          LineHeight = 18
          PopupMenu = popProject
          ShowLeafButton = False
          SortSection = -1
          StoragePath = '\Tree'
          TabOrder = 1
          TabStop = True
          VertScrollBarStyles.ShowTrackHint = True
          VertScrollBarStyles.Width = 17
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
      Left = 576
      Top = 285
      Width = 218
      Height = 276
      Buttons = [pbPin, pbMaximize]
      ParentBackground = False
      TabOrder = 10
      Caption = 'Properties'
      object Splitter1: TSplitter
        Left = 0
        Top = 233
        Width = 218
        Height = 3
        Cursor = crVSplit
        Align = alBottom
        AutoSnap = False
        MinSize = 40
        ResizeStyle = rsUpdate
        ExplicitTop = 225
        ExplicitWidth = 63
      end
      object lmdProperties: TLMDSimplePropInspector
        Left = 0
        Top = 21
        Width = 218
        Height = 212
        PropKinds = [pkProperties, pkReadOnly]
        SortType = stNone
        ArrangeKind = akByCategory
        GridVisible = False
        GutterVisible = True
        CursorVisible = True
        SelectionStyle = ssFlat
        CategoryFont.Charset = DEFAULT_CHARSET
        CategoryFont.Color = clHighlightText
        CategoryFont.Height = -11
        CategoryFont.Name = 'Tahoma'
        CategoryFont.Style = [fsBold]
        Splitter = 84
        Align = alClient
        Color = clWindow
        Constraints.MinWidth = 200
        TabOrder = 0
        OnClick = lmdPropertiesClick
      end
      object Panel2: TPanel
        Left = 0
        Top = 236
        Width = 218
        Height = 40
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
          Width = 212
          Height = 34
          Align = alClient
          Caption = 'Property information'
          Transparent = True
          WordWrap = True
          ExplicitWidth = 99
          ExplicitHeight = 13
        end
      end
    end
    object dpSearchResults: TLMDDockPanel
      Left = 6
      Top = 357
      Width = 564
      Height = 183
      ParentBackground = False
      TabOrder = 7
      Caption = 'Search Results'
    end
    object dpTodo: TLMDDockPanel
      Left = 6
      Top = 357
      Width = 564
      Height = 183
      ParentBackground = False
      TabOrder = 9
      Caption = 'Todo'
    end
    object LMDDockPanel2: TLMDDockPanel
      Left = 6
      Top = 6
      Width = 564
      Height = 345
      PanelVisible = False
      ParentBackground = False
      TabOrder = 4
      Caption = 'dpEditors'
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 800
    Height = 33
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object tbrMain: TToolBar
      Left = 0
      Top = 0
      Width = 384
      Height = 33
      Align = alLeft
      AutoSize = True
      ButtonHeight = 32
      ButtonWidth = 32
      EdgeInner = esNone
      EdgeOuter = esNone
      Flat = False
      Images = imgToolbar
      TabOrder = 0
      Transparent = False
      StyleElements = [seFont, seClient]
      Wrapable = False
      object ToolButton15: TToolButton
        Left = 0
        Top = 0
        Action = actFileNewAsset
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton3: TToolButton
        Left = 32
        Top = 0
        Action = actFileProjectSave
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton1: TToolButton
        Left = 64
        Top = 0
        Width = 8
        Caption = 'ToolButton1'
        ImageIndex = 7
        Style = tbsSeparator
      end
      object ToolButton4: TToolButton
        Left = 72
        Top = 0
        Action = actEditUndo
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton5: TToolButton
        Left = 104
        Top = 0
        Action = actEditRedo
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton6: TToolButton
        Left = 136
        Top = 0
        Width = 8
        Caption = 'ToolButton6'
        ImageIndex = 1
        Style = tbsSeparator
      end
      object btnEditCopy: TToolButton
        Left = 144
        Top = 0
        Action = actEditCopy
        ParentShowHint = False
        ShowHint = True
      end
      object btnEditCut: TToolButton
        Left = 176
        Top = 0
        Action = actEditCut
        ParentShowHint = False
        ShowHint = True
      end
      object btnEditPaste: TToolButton
        Left = 208
        Top = 0
        Action = actEditPaste
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton11: TToolButton
        Left = 240
        Top = 0
        Width = 8
        Caption = 'ToolButton11'
        ImageIndex = 9
        Style = tbsSeparator
      end
      object ToolButton10: TToolButton
        Left = 248
        Top = 0
        Action = actEditZoomIn
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton12: TToolButton
        Left = 280
        Top = 0
        Action = actEditZoomOut
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton13: TToolButton
        Left = 312
        Top = 0
        Action = actEditZoomReset
        ParentShowHint = False
        ShowHint = True
      end
      object ToolButton2: TToolButton
        Left = 344
        Top = 0
        Width = 8
        Caption = 'ToolButton2'
        ImageIndex = 19
        Style = tbsSeparator
      end
      object btnBuildRun: TToolButton
        Left = 352
        Top = 0
        Action = actGameRun
        ParentShowHint = False
        ShowHint = True
      end
    end
    object tbrSettings: TToolBar
      Left = 728
      Top = 0
      Width = 72
      Height = 33
      Align = alRight
      AutoSize = True
      ButtonHeight = 32
      ButtonWidth = 32
      Images = imgToolbar
      TabOrder = 1
      object btnEditorHelp: TToolButton
        Left = 0
        Top = 0
        Action = actEditorHelp
        ParentShowHint = False
        ShowHint = True
        Visible = False
      end
      object ToolButton14: TToolButton
        Left = 32
        Top = 0
        Width = 8
        Caption = 'ToolButton14'
        ImageIndex = 6
        Style = tbsSeparator
        Visible = False
      end
      object btnSettings: TToolButton
        Left = 40
        Top = 0
        Hint = 'Application Settings'
        Action = actSettings
        ParentShowHint = False
        ShowHint = True
      end
    end
  end
  object actActions: TActionList
    Left = 88
    Top = 88
    object actFileProjectSave: TAction
      Category = 'File'
      Caption = '&Save'
      Hint = 'Save project'
      ImageIndex = 6
      ShortCut = 16467
      OnExecute = actFileProjectSaveExecute
    end
    object actFileProjectClose: TAction
      Category = 'File'
      Caption = '&Close'
      Hint = 'Close project'
      ImageIndex = 3
      ShortCut = 16499
      OnExecute = actFileProjectCloseExecute
    end
    object actEditCopy: TAction
      Category = 'Edit'
      Caption = '&Copy'
      Hint = 'Copy'
      ImageIndex = 7
      ShortCut = 16451
      OnExecute = actEditCopyExecute
    end
    object actEditCut: TAction
      Category = 'Edit'
      Caption = 'Cu&t'
      Hint = 'Cut'
      ImageIndex = 8
      ShortCut = 16472
      OnExecute = actEditCutExecute
    end
    object actEditPaste: TAction
      Category = 'Edit'
      Caption = '&Paste'
      Hint = 'Paste'
      ImageIndex = 10
      ShortCut = 16470
      OnExecute = actEditPasteExecute
    end
    object actHelp: TAction
      Category = 'Help'
      Caption = '&Help'
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
      ImageIndex = 1
      ShortCut = 16474
      OnExecute = actEditUndoExecute
    end
    object actEditRedo: TAction
      Category = 'Edit'
      Caption = '&Redo'
      Enabled = False
      Hint = 'Redo'
      ImageIndex = 0
      ShortCut = 24666
      OnExecute = actEditRedoExecute
    end
    object actEditZoomIn: TAction
      Category = 'Edit'
      Caption = 'Zoom &In'
      Hint = 'Zoom In'
      ImageIndex = 20
      OnExecute = actEditZoomInExecute
    end
    object actEditZoomOut: TAction
      Category = 'Edit'
      Caption = 'Zoom &Out'
      Hint = 'Zoom Out'
      ImageIndex = 19
      OnExecute = actEditZoomOutExecute
    end
    object actEditZoomReset: TAction
      Category = 'Edit'
      Caption = 'Zoom &Reset'
      Hint = 'Zoom Reset'
      ImageIndex = 18
      OnExecute = actEditZoomResetExecute
    end
    object actFileNewAsset: TAction
      Category = 'File'
      Caption = 'New Image...'
      Hint = 'Create a new game image'
      ImageIndex = 2
      ShortCut = 16462
      OnExecute = actFileNewAssetExecute
    end
    object actEditFind: TAction
      Category = 'Edit'
      Caption = 'Find...'
      Hint = 'Search the active document'
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
      ImageIndex = 12
      ShortCut = 16463
      OnExecute = actFileProjectOpenExecute
    end
    object actNewAsset: TAction
      Caption = 'New Image (Default Size)'
      ImageIndex = 2
      OnExecute = actNewAssetExecute
    end
    object actDeleteAsset: TAction
      Caption = 'Delete Image'
      ImageIndex = 9
      ShortCut = 8238
      OnExecute = actDeleteAssetExecute
    end
    object actSettings: TAction
      Caption = 'Settings...'
      Hint = 'Show the application settings dialog'
      ImageIndex = 4
      ShortCut = 24698
      OnExecute = actSettingsExecute
    end
    object actEditorHelp: TAction
      Caption = 'Help'
      Hint = 'Show Editor Help'
      ImageIndex = 14
      OnExecute = actEditorHelpExecute
    end
    object actNewAssetCustom: TAction
      Caption = 'New Asset... (Custom Size)'
      ImageIndex = 2
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
      ImageIndex = 21
      SecondaryShortCuts.Strings = (
        'F5')
      ShortCut = 120
      OnExecute = actGameRunExecute
    end
  end
  object mnuMain: TMainMenu
    Left = 28
    Top = 88
    object mnuFile: TMenuItem
      Caption = '&File'
      object NewAsset1: TMenuItem
        Action = actFileNewAsset
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object OpenProject1: TMenuItem
        Action = actFileProjectOpen
      end
      object mnuFileMru: TMenuItem
        Caption = 'Reopen'
        object TMenuItem
        end
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
    end
    object mnuView: TMenuItem
      Caption = '&View'
      object BuildResults1: TMenuItem
        Action = actViewBuildResults
        AutoCheck = True
      end
      object SearchResults1: TMenuItem
        Action = actViewSearchResults
        AutoCheck = True
      end
      object Messages1: TMenuItem
        Action = actViewMessages
        AutoCheck = True
      end
      object odo1: TMenuItem
        Action = actViewTodo
        AutoCheck = True
      end
      object EditorKeys1: TMenuItem
        Action = actViewEditorKeys
        AutoCheck = True
      end
    end
    object mnuGame: TMenuItem
      Caption = '&Game'
      object Run1: TMenuItem
        Action = actGameRun
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      object mnuHelp: TMenuItem
        Action = actHelp
      end
      object mnuHelpGettingStarted: TMenuItem
        Action = actHelpGettingStarted
      end
      object mnuHelpKeymapReference: TMenuItem
        Action = actHelpKeymapReference
        Visible = False
      end
      object mnuHelpTipOfTheDay: TMenuItem
        Action = actHelpTipOfTheDay
        Visible = False
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
      end
    end
  end
  object DockManager: TLMDDockManager
    StyleName = 'VCLStyle'
    Left = 154
    Top = 88
  end
  object imgProject: TImageList
    ColorDepth = cd32Bit
    Left = 24
    Top = 200
    Bitmap = {
      494C010105000800040010001000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000002000000001002000000000000020
      0000000000000000000000000000000000000000000080827BFF80817DFF8080
      80FF80817DFF808080FF00000000000000001B415BB23D93CFFF3D91CEFF3D92
      CEFF3D92CFFF3D94D0FF214D6BBE000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000808676FFFFFFFFFFFFFF
      FFFFFFFFFFFF80817DFF00000000000000003B93D1FFA9F9FFFF8FF0FFFF8FEF
      FFFF8DF0FFFFD2FFFFFF3D94D0FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000808080FFFFFFFFFFFFFF
      FFFFFFFFFFFF808080FF666666FF666666FF3390D1FFB7F3FFFF76E0FDFF76E0
      FDFF75E0FEFFDAFEFFFF3A92CFFF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000808676FFFFFFFFFFFFFF
      FFFFFFFFFFFF80817DFF00000000000000003090D2FFCEF7FFFFB5EEFEFFDBF9
      FFFFDDFBFFFFE2FFFFFF3C94D0FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080827BFF80817DFF8080
      80FF80817DFF808080FF00000000000000003592D2FFDCFDFFFFDAFBFFFF338D
      CDFF3891CEFF3C94D0FF1F4764B0000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000001C4460AC3C94D0FF3C94D0FF1C40
      5BA8000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000808080FF7C7C7CFF7C7C
      7CFF7C7C7CFF7C7C7CFF00000000000000001B415BB23D93CFFF3D91CEFF3D92
      CEFF3D92CFFF3D94D0FF214D6BBE000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007C7C7CFFFFFFFFFFFFFF
      FFFFFFFFFFFF7C7C7CFF00000000000000003B93D1FFA9F9FFFF8FF0FFFF8FEF
      FFFF8DF0FFFFD2FFFFFF3D94D0FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007C7C7CFFFFFFFFFFFFFF
      FFFFFFFFFFFF7C7C7CFF666666FF666666FF3390D1FFB7F3FFFF76E0FDFF76E0
      FDFF75E0FEFFDAFEFFFF3A92CFFF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007C7C7CFFFFFFFFFFFFFF
      FFFFFFFFFFFF80817DFF00000000000000003090D2FFCEF7FFFFB5EEFEFFDBF9
      FFFFDDFBFFFFE2FFFFFF3C94D0FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007C7C7CFF7C7C7CFF7C7C
      7CFF7C7C7CFF7C7C7CFF00000000000000003592D2FFDCFDFFFFDAFBFFFF338D
      CDFF3891CEFF3C94D0FF1F4764B0000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000006969
      69FF000000000000000000000000000000001C4460AC3C94D0FF3C94D0FF1C40
      5BA8000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000006969
      69FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080827BFF80817DFF85AC
      49FF80817DFF808080FF00000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000808080FF808080FF8080
      80FF808080FF808080FF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080827BFF80817DFF8080
      80FF80817DFF808080FF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000808676FFE8EEDFFF85AC
      49FFE3EBD8FF80817DFF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000DBDDEAFF656D98FFB9C1EBFFB9C1
      EBFFB9C1EBFF656D98FFDDDFECFF00000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF0000000000000000808676FFFFFFFFFFFFFF
      FFFFFFFFFFFF80817DFF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF000000000000000000000000000000000000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF000000000000000085AD49FF85AD49FF85AD
      49FF85AD49FF85AD49FF666666FF666666FFB3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000B2BAE4FF2F48CCFF2F48CCFF2F48
      CCFF2F48CCFF2F48CCFF545C87FF666666FFB3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF0000000000000000808080FFFFFFFFFFFFFF
      FFFFFFFFFFFF808080FF666666FF666666FFB3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF000000000000000000000000000000000000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF0000000000000000808676FFE8EEDFFF85AC
      49FFE3EBD8FF80817DFF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000DDDFECFF656D98FFB9C1EBFFB9C1
      EBFFB9C1EBFF656D98FFDDDFECFF00000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF0000000000000000808676FFFFFFFFFFFFFF
      FFFFFFFFFFFF80817DFF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF000000000000000000000000000000000000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF000000000000000080827BFF80817DFF85AC
      49FF80817DFF808080FF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF0000000000000000808080FF808080FF8080
      80FF808080FF808080FF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF000000000000000080827BFF80817DFF8080
      80FF80817DFF808080FF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF000000000000000000000000000000000000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000808080FF80817DFF85AC
      49FF80817DFF808080FF00000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000808080FF808080FF8080
      80FF808080FF808080FF00000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000808080FF7C7C7CFF7C7C
      7CFF7C7C7CFF7C7C7CFF00000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFF00FFFFFF00FFFFFF00FFFFFF
      00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF
      00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF0000000080817DFFE8EEDFFF85AC
      49FFE8EFDFFF7C7D7AFF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000DDDFECFF656D98FFB9C1EBFFB9C1
      EBFFB9C1EBFF636B96FFDDDFECFF00000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000000000007C7C7CFFFFFFFFFFFFFF
      FFFFFFFFFFFF7C7C7CFF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000FFFF00FFFFFF00FFFFFF00FFFFFF
      00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFB3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFFFFF00FF0000000085AD49FF85AD49FF85AD
      49FF85AD49FF85AD49FF666666FF666666FFB3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000B2BAE4FF2F48CCFF2F48CCFF2F48
      CCFF2F48CCFF2F48CCFF545C87FF666666FFB3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000000000007C7C7CFFFFFFFFFFFFFF
      FFFFFFFFFFFF7C7C7CFF666666FF666666FFB3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000FFFF00FFFFFF00FFFFFF00FFFFFF
      00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFB3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFFFFF00FF0000000080817DFFE8EEDFFF85AC
      49FFE8EFDFFF80817DFF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000DDDFECFF656D98FFB9C1EBFFB9C1
      EBFFB9C1EBFF656D98FFDDDFECFF00000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000000000007C7C7CFFFFFFFFFFFFFF
      FFFFFFFFFFFF80817DFF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000FFFF00FFFFFF00FFFFFF00FFFFFF
      00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFB3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFFFFF00FF000000007C7C7CFF80817DFF85AC
      49FF80817DFF7C7C7CFF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000000000007C7C7CFF808080FF8080
      80FF808080FF7C7C7CFF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000000000007C7C7CFF7C7C7CFF7C7C
      7CFF7C7C7CFF7C7C7CFF0000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFF00000000FFFF00FFFFFF00FFFFFF00FFFFFF
      00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFB3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFFFFF00FF0000000000000000000000006969
      69FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000006969
      69FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000006969
      69FF000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFF00FFFFFF00FFFFFF00FFFFFF
      00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF
      00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF0000000000000000000000006969
      69FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000006969
      69FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000006969
      69FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000B3763CFFB3763CFFB3763CFFB376
      3CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFFB3763CFF0000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000200000000100010000000000000100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
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
  object imgProjectNodes: TImageList
    ColorDepth = cd32Bit
    Left = 94
    Top = 200
    Bitmap = {
      494C010118003000040010001000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000007000000001002000000000000070
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
      2800000040000000700000000100010000000000800300000000000000000000
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
      000000000000}
  end
  object dlgOpen: TOpenTextFileDialog
    DefaultExt = 'agdx'
    Filter = 'AGDX Project|*.agdx|All Files|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Title = 'Open an Existing AGDX Project'
    Left = 172
    Top = 140
  end
  object popProject: TPopupMenu
    OnPopup = popProjectPopup
    Left = 224
    Top = 88
    object mnuNewAsset: TMenuItem
      Action = actNewAsset
    end
    object btnNewImageCustom: TMenuItem
      Action = actFileNewAsset
    end
    object DeleteAsset1: TMenuItem
      Action = actDeleteAsset
    end
  end
  object imgBuildNodes: TImageList
    ColorDepth = cd32Bit
    Left = 94
    Top = 264
    Bitmap = {
      494C01010D001800040010001000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000004000000001002000000000000040
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000330000
      0033000000220000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000003300000033000000330000
      0033000000330000003300000033000000330000003300000033008B46FF00C6
      83FF004021B90000003300000033000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000002D9271FF2D9170FF2D906FFF2A90
      6EFF1F906DFFA7826CFFA7856FFFAA8672FFAE8674FFB88575FF008944FF00E4
      A5FF00BE7EFF118B56FF339073FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000002C8462FF2AB281FF28B383FF22A8
      78FF147855FFFFFAF1FF008475FF008940FF008942FF008843FF008440FF00D9
      A1FF00D8A0FF00BB7DFF11844FFF000000220000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000001001850775CFF178B5CFF6097
      7AFFDAD6C7FFFFF0E8FF008238FF3BE7BFFF00D7A0FF00D7A0FF00D59FFF00D0
      9CFF00D09CFF00D39FFF00B980FF004222BA0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000AC8874FFFFF8EFFFFFEB
      DEFFFEEBDEFFFFEFE5FF008137FF6AE7CEFF00C899FF00C899FF00C899FF00C7
      97FF00C898FF00CA9AFF62E6CDFF008A46FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000A18972FFFEF4EBFFCAB7
      A5FFCFBAA9FFA27E6AFF008339FF91EEE0FF4AE8D3FF4DE7D3FF4CE6D1FF93E8
      D8FF00C397FF5FE0C6FF00B281FF003F20AC0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000009F8B74FFFDF4EBFFF2E4
      D5FFCCB9A7FFFFECE0FF3B9A65FF008339FF008239FF00823AFF008037FF80E4
      D5FF56DAC3FF00AD7CFF00381CA4000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000A08D76FFFCF5EDFFC7B6
      A2FFC9B9A6FFCEBAA8FFD6BDACFFDCBEAEFFE1BFB0FFECC1B4FF00843AFF70E1
      D4FF00A878FF3E8A58FF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000A49078FFFDF6EFFFF0E0
      D0FFC9B7A4FFF3E4D5FFCBB8A6FFF5E4D6FFCFB9A7FFFFE8DCFF008237FF00A3
      77FF53B081FFBC9481FF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000A6927AFFFDF7F2FFC7B4
      9FFFC9B7A3FFC9B7A4FFCAB7A4FFC9B7A4FFCAB7A4FFCFB8A6FFD9BAA9FFDAB8
      A7FFFFFBF8FFAD947DFF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000A8947DFFFEFAF4FFECDB
      CBFFC8B7A3FFEFDFD0FFC8B7A4FFEFDFD0FFC8B7A4FFF0DFD0FFCAB7A4FFEFDC
      CCFFFFFAF5FFA9947DFF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000AA9680FFFFFCF8FFC4B1
      9CFFC6B5A0FFC7B6A1FFC7B6A1FFC7B6A1FFC7B6A1FFC7B6A1FFC6B5A0FFC4B1
      9CFFFFFCF8FFAA9680FF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000AD9983FFFFFEFBFFE7D4
      C1FFC3B09CFFE9D7C4FFC4B19DFFE9D7C4FFC4B19DFFE9D7C4FFC3B09CFFE7D4
      C1FFFFFEFBFFAD9983FF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B09D87FFFFFFFCFFFFFC
      F8FFFFFCF9FFFFFDFAFFFFFDFAFFFFFDFAFFFFFDFAFFFFFDFAFFFFFCF9FFFFFC
      F8FFFFFFFCFFB09D87FF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000554D42B0B29F8AFFB19E
      88FFB19E87FFB19E87FFB19E87FFB19E87FFB19E87FFB19E87FFB19E87FFB19E
      88FFB29F8AFF554D42B000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000002A000000330000002A000000000000
      0000000000000000000000000000000000000000000000000023000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002300000000000000000000000000000000000000000000
      0000000000000000000000000000000000330000000000000000000000000000
      0000000000000000000000000000000000000000002300000033000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000230000000000000000000000000000000000000000000000000000
      000000000000000000000000002D795632DDA77644FF795632DD0000002D0000
      000000000000000000000000000000000000000000005C5C5BC0B0B0ADFFAFAF
      ACFFAEAEABFFADADABFFADADABFFADADABFFADADABFFADADABFFADADABFFAEAE
      ABFFAFAFADFF5C5C5BC000000000000000000000000000000000000000000000
      00000000000000000000000000331D72A8FF0000003300000000000000000000
      0000000000000000000000000000000000005C5C5BC0AFAFADFFAEAEACFFAFAE
      ACFFB0AFADFFAFAFADFFB0AFADFFB0AFADFFAFAFACFFAEAEABFFAEAEABFFAFAF
      ADFF5C5C5BC00000000000000000000000000000000000000000000000000000
      0000000000000000002D865F36E9C5A37DFFFBF4E7FFC5A37DFF865F36E90000
      002D0000000000000000000000000000000000000000B0B0ADFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFB0B0ADFF00000000000000000000000000000000000000000000
      000000000000000000331A6CA4FF65F0FFFF1A6CA3FF00000033000000000000
      000000000000000000000000000000000000B0B0ADFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFB0B0ADFF0000000000000000000000000000000000000000000000000000
      00000000002D855F36E8C4A47EFFF6EDDFFFC19E78FFF6EDDFFFC4A47EFF855F
      36E80000002D00000000000000000000000000000000B0B0ACFFFFFFFFFF0010
      DBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFE
      FEFFFFFFFFFFAEAEABFF00000000000000000000000000000000000000000000
      0000000000331A6CA3FF62E8FFFF54E0FFFF62E7FFFF196BA2FF000000330000
      000000000000000000000000000000000000AEAEABFFFFFFFFFFFFFFFFFFD9CE
      D3FF007023FFE5D7DBFF455A6FFF375779FF357DCEFFFFFFFFFFFFFFFFFFFFFF
      FFFFAEAEABFF0000000000000000000000000000000000000000000000000000
      002D855F36E8C5A581FFF8F1E6FFB4895CFFA3713DFFB4895CFFF8F1E6FFC5A5
      81FF855F36E80000002D000000000000000000000000B0B0ABFFFFFFFFFF5682
      EAFFFFFFFDFF989795FFC1C1C1FFFFFEFEFF979797FFC2C2C2FFBFC0C0FFFCFB
      FBFFFFFFFFFFADADABFF00000000000000000000000000000000000000000000
      00331A6CA3FF4CC4F0FF4EDBFFFF4CDAFFFF4DDAFFFF65E6FFFF196BA2FF0000
      003300000000000000000000000000000000ADADABFFFFFFFFFFFFFFFFFF006D
      1FFFE7D7DDFF007726FF587EA0FF7CA4B4FF87CFFCFF1D5790FFFFFFFFFFFFFF
      FFFFAFAFACFF00000000000000000000000000000000000000000000002D855F
      36E8C7A684FFFAF4EAFFB3895BFFA26F3BFFA3703CFFA26F3BFFB3895BFFFAF4
      EAFFC7A684FF855F36E80000002D0000000000000000B0AFABFFFFFFFFFF0012
      DBFFFFFFF9FFFDFCFAFFFAFAFAFFF9F9F9FFFAFAFBFFFAFAFBFFF9F9F9FFF8F8
      F8FFFFFFFFFFADADABFF00000000000000000000000000000000000000331A6C
      A3FF69E6FFFF4AD5FFFF49D7FFFF461C10FF48D6FFFF49D4FFFF69E5FFFF1A6C
      A3FF00000033000000000000000000000000ADADABFFFFFFFFFFFEFBFCFFD3CC
      CFFFD8D0D3FFE0D3D2FF3CAAF2FF89E4FFFF7DD3FFFF0B95FFFF235B90FFFFFF
      FFFFB6B3AEFF0000000000000000000000000000000000000026865E35E9C6A7
      84FFFCF7EFFFB38A5EFFB89167FFFAF2E4FFF8EFE0FFFBF3E6FFB99268FFB38B
      5EFFFCF7EFFFC6A784FF865E35E90000002A00000000AFAFABFFFFFFFFFFFFFF
      F5FFFFFDF4FFF7F7F5FFF6F6F5FFF5F5F4FFF6F6F4FFF6F6F5FFF5F5F4FFF4F4
      F3FFFFFFFFFFADADABFF000000000000000000000000000000331A6CA3FF4DC1
      F0FF43D1FFFF43CEFFFF43D4FFFF39A1CAFF43D4FFFF43CEFFFF43D0FFFF4DC1
      F0FF1A6CA3FF000000330000000000000000ADADABFFFFFFFFFFF9F7F7FFFFFC
      FDFFFFFFFFFFFFFFFEFFFFFFF9FF1D6EC2FF3DC4FFFF29A9FFFF1298FFFF2960
      95FFC5BBB1FF0000000000000000000000000000000064472ACCC8A887FFFDF9
      F2FFB58C5FFFA67542FFA57441FFB89065FFFDF8EFFFA26E39FFA77644FFA675
      43FFB58C5FFFFDF9F2FFC8A887FF785632DD00000000B0AFABFFFFFFFFFF0012
      DBFFFFFCF2FFF7F7F4FFF5F5F4FFF4F4F3FFF4F4F2FFF4F5F3FFF4F4F2FFF2F2
      F1FFFFFFFFFFADADABFF000000000000000000000033186CA3FF6EE2FFFF3DCC
      FFFF3EC9FFFF3ECAFFFF3CD1FFFF644132FF3CD1FFFF3ECAFFFF3EC9FFFF3DCC
      FFFF6EE2FFFF186CA3FF0000003300000000ADADABFFFFFFFFFFFAF5F6FFDACF
      D4FF006F22FFDDD0D5FFFFFAF9FFFFFFF6FF2573C4FF43C7FFFF2AABFFFF119B
      FFFF28659FFF00000033000000000000000000000000A67442FFFFFFFFFFC4A4
      81FFA3713DFFA87746FFA67441FFB99166FFFFFFFEFFA4713DFFA97949FFA979
      48FFA4713DFFC4A481FFFFFFFFFFA67442FF00000000B0B0ABFFFFFFFFFF527D
      E4FFFFFCF1FF9C9C9AFFBFBFBFFFBEBEBEFFF4F3F3FF989898FFBDBDBDFFF0EF
      F0FFFFFFFFFFADADABFF00000000000000001B72A8FF9BF5FFFF35C8FFFF38C4
      FFFF3AC4FFFF3AC6FFFF38CEFFFF59392CFF38CEFFFF3AC6FFFF3AC4FFFF38C4
      FFFF35C8FFFF9BF5FFFF1B72A8FF00000000ADADABFFFFFFFFFFFAF5F6FF006E
      20FFE7D6DDFF007024FFFFFBFEFFFFFAF7FFA0948BFF2573C4FF3FC6FFFF1FAA
      FFFF83B0D7FF7D7770FF0000003300000000000000004B351FACC9A989FFFFFF
      FCFFB48D61FFA57341FFBE9A73FFFFFFFFFFFFFFFFFFA57340FFA97948FFA776
      43FFB58D62FFFFFFFCFFC9A989FF5E4327C100000000B0AFABFFFFFFFFFF0013
      DDFFFCF7EDFFF3F1EEFFF1F0EFFFF0EFEDFFEFEEEDFFF0EEEDFFEFEEECFFEDEC
      EAFFFFFFFFFFADADABFF000000000000000000000000186CA3FF77E0FFFF31C1
      FFFF33C0FFFF34C2FFFF33CBFFFF4F2F23FF33CBFFFF34C2FFFF33C0FFFF31C1
      FFFF77E0FFFF186CA3FF0000000000000000ADADABFFFFFFFFFFF3EFEFFFD4CD
      D0FFD7D0D4FFDDD1D7FF006B1DFFFAF2F3FFF9F3EFFFFFF7EEFF1B6FC4FFACD9
      EEFF91887EFFC1BFB8FF767B6DFF00000033000000000000000047321CA7C9AA
      8BFFFFFFFFFFB68C61FFA3713CFFA26F3AFFA26F3AFFA67542FFA67542FFB78D
      62FFFFFFFFFFC9AA8BFF47321CA70000000000000000AFAFABFFFFFFFFFFFDF8
      E9FFF5F2EAFFEDEDEAFFEBEBEAFFEAEAE9FFF4F4F3FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFAEAEABFF00000000000000000000000000000000196CA2FF7BDF
      FFFF2BBDFFFF2EBEFFFF2EC7FFFF442518FF2EC6FFFF2DBEFFFF2BBDFFFF7BDF
      FFFF196CA2FF000000000000000000000000ADADABFFFFFFFFFFEBEAE9FFEDED
      ECFFEFEEEEFFF3EFEFFFF4EEF0FFF9F6F6FFFFFFFFFFFFFFFFFFFFFFFFFF8078
      72FFE9E6E2FF888B82FFBA79B6FF9868CAFF0000000000000000000000004732
      1CA7CAAB8CFFFFFFFFFFB58C60FFBA946AFFFFFFFEFFA3703CFFB68E62FFFFFF
      FFFFCAAB8CFF47321CA7000000000000000000000000B0AFABFFFFFFFFFF0014
      DDFFF7F2E7FFEEECE9FFEAE9E8FFE8E6E5FFFFFFFFFFCBCBCAFFA7A7A4FFA5A5
      A3FFFFFFFFFFAFAFADFF0000000000000000000000000000000000000000196D
      A2FF7DDFFFFF28BBFFFF29C0FFFF3A1606FF29C0FFFF26BAFFFF7CDEFFFF196C
      A2FF00000000000000000000000000000000ADAEABFFFFFFFFFFE7E6E4FFE8E7
      E6FFE9E7E6FFE9E7E7FFE8E6E6FFFFFFFFFFCCCCCAFFA8A7A5FFA9A8A6FFFFFF
      FFFF7C7D76FFE1B1DFFFCB96C6FFAE7CCEFF0000000000000000000000000000
      000047321CA7CAAC8EFFFFFFFFFFB38A5EFFA06B35FFB48B5FFFFFFFFFFFCAAC
      8EFF47321CA700000000000000000000000000000000B0B0ABFFFFFFFFFF4E78
      E0FFF5F0E6FF9D9C9BFFBABAB9FFE5E4E4FFFFFFFFFFA7A7A4FFEBEAEAFFFFFF
      FFFFE9E9E9FF4F4F4EAC00000000000000000000000000000000000000000000
      00001A6EA3FF51B8F1FF21B9FFFF22BAFFFF20B8FFFF81DDFFFF196CA2FF0000
      000000000000000000000000000000000000AEAEABFFFFFFFFFFE3E3E2FFE4E4
      E3FFE4E5E4FFE4E4E3FFE3E3E2FFFFFFFFFFA7A7A4FFEBEBEAFFFFFFFFFFEAEB
      EAFF3E403D98C087D5FFBE8AD3FF000000000000000000000000000000000000
      00000000000046321CA7CBAD8EFFFFFFFFFFC6A886FFFFFFFFFFCBAD8FFF4632
      1CA70000000000000000000000000000000000000000B0B0ACFFFFFFFFFF0012
      DDFFEEEAE0FFE6E5E2FFE3E2E1FFE1DFDEFFFFFFFFFFA5A5A3FFFFFFFFFFE8E8
      E8FF4B4B49A70000000000000000000000000000000000000000000000000000
      0000000000001A6EA3FF83DCFFFF15B2FFFF82DBFFFF196DA2FF000000000000
      000000000000000000000000000000000000AEAEACFFFFFFFFFFE0DFDEFFE1DF
      DEFFE1E0DFFFE1DFDEFFE0DFDEFFFFFFFFFFA5A5A3FFFFFFFFFFE8E8E8FF4949
      48A6000000000000000000000000000000000000000000000000000000000000
      0000000000000000000046321CA7CBAE91FFFFFFFFFFCBAE91FF46321CA70000
      00000000000000000000000000000000000000000000B0B0ADFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE9E9E9FF4949
      48A6000000000000000000000000000000000000000000000000000000000000
      00000000000000000000176DA4FFD0F9FFFF176DA3FF00000000000000000000
      000000000000000000000000000000000000AFAFADFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE9E9E9FF494948A60000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000004B351FACA67440FF4B351FAC000000000000
      000000000000000000000000000000000000000000009D9D9BEFB0B0ADFFB0AF
      ACFFAFAEABFFAEAEABFFAEAEABFFADAEABFFAEAEABFFAFAFADFF949493EA0000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000001A72A8FF0000000000000000000000000000
      0000000000000000000000000000000000009D9D9BEFB0B0ADFFAEAEACFFAEAE
      ABFFAEAEABFFAEAEABFFADAEABFFAEAEABFFAFAFADFF949493EA000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000001E00000031000000330000003300000033000000310000001E0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000030000000330000003300000033000000330000
      0033000000330000003300000033000000300000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000E0000
      0033452B0AAAA96816F9B26E17FFB26E17FFB26E17FFA96816F9452B0AAA0000
      00330000000E0000000000000000000000000000000000000000000000000000
      00000000000000000000A57727F2B68123FFB57E1FFFB57E1EFFB57E1EFFB57E
      1EFFB57E1EFFB57E1FFFB68123FFA57727F20000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000E140C036BB26D
      15FFC27B2AFFD08637FFD48939FFD48939FFD48939FFD08637FFC27B2AFFB26D
      15FF140C036B0000000E00000000000000000000000000000000000000000000
      00000000000000000000B68224FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFB68123FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0019000000330000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000140C036BB46E17FFD089
      3AFFDCB380FFE4F4EDFFEBFFFFFF9AABB2FFEBFFFFFFE4F4EDFFDCB380FFD089
      3AFFB46E17FF140C036B00000000000000000000003000000033000000330000
      00330000003300000033B58021FFFFFFFFFFEADDBAFFEADCB8FFE8D9B3FFE7D7
      B1FFE6D6AFFFE6D6AEFFFFFFFFFFB57E1EFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000028
      1696008C4AFF0000003300000000000000000000002300000033000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000003300000033000000230000001EB16C14FFD48D41FFDECC
      ACFFE2FFFFFFE1FFFFFFE2FFFFFFE3FFFFFFE2FFFFFFE1FFFFFFE2FFFFFFDECC
      ACFFD48D41FFB16C14FF0000001E00000000A57727F2B68123FFB57E1FFFB57E
      1EFFB57E1EFFB47D1DFFB37A19FFB07611FFB07511FFBB8A31FFEADCB8FFE7D7
      B1FFE6D6AFFFE5D5ACFFFFFFFFFFB47D1DFF0000001F00000033000000330000
      0033000000330000003300000033000000330000003300000033000000330088
      46FF53DAB0FF008745FF00000033000000004C4C4EC08F9297FF8D9299FF8D93
      9BFF8D939BFF8D929AFF8D9299FF8D929AFF8D9197FF8C8D8FFF8B8B8BFF8A8A
      8AFF8A8A8AFF8B8B8BFF8D8D8DFF4B4B4BC0452B09A9C98434FFDDB98BFFDCFF
      FFFFDBFBFFFFDBF9FDFFDCFAFDFFDCF9FDFFDBF8FCFFDBF9FCFFDBFBFFFFDCFF
      FFFFDDB98BFFC98434FF452B09A900000000B68123FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB0750FFFFCFBF4FFF9F4
      E9FFF8F2E6FFF8F2E5FFFFFFFFFFB47D1DFF00391FAE008A48FF008946FF0089
      46FF008946FF008946FF008946FF008946FF008946FF008845FF008643FF00B9
      7EFF00D8A0FF64D7B3FF008743FF000000338F9297FFF8C479FFF2BE75FFDB99
      3FFFDB9941FFF1C078FFF1BF77FFDB9A41FFDC983BFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFF8D8D8DFFA96714F9DD9A51FFD9F0ECFFD6FB
      FFFFD6F8FBFFD8F9FCFFDBFDFFFFDAFCFFFFD8F8FBFFD6F6F9FFD6F7FAFFD6FB
      FFFFD9F0ECFFDD9A51FFA96714F900000000B57E1EFFFFFFFFFFE6D6AEFFE6D6
      AFFFE6D7B0FFE6D7B0FFE6D6AFFFE6D6AEFFFFFFFFFFAE730DFFF8F5E7FFF4EE
      DCFFF3ECD9FFF3ECD8FFFFFFFFFFB47D1DFF008A48FF00D5A7FF00D1A1FF00D0
      A0FF00D0A0FF00D0A0FF00D0A0FF00D0A0FF00D0A0FF00D0A0FF00CF9FFF00CD
      9CFF00CB9AFF00CD9CFF73DABDFF008A47FF8D9197FFE6B26BFFEFC383FFEEC4
      86FFD79C4CFFD79C4CFFEEC486FFEDC283FFDA9F4BFFF6FAFFFFF5F5F6FFF5F4
      F4FFF5F4F4FFF6F5F5FFFFFFFFFF8B8C8CFFB16C14FFE9A662FFD3FFFFFFD2F6
      FDFFD2F5FAFFD7FBFFFF534846FFB3CCCEFFD6FAFFFFD2F5FAFFD1F3F9FFD2F6
      FDFFD3FFFFFFE9A662FFB16C14FF00000000B47D1DFFFFFFFFFFE5D5ACFFE6D6
      AFFFE6D6AFFFE6D6AFFFE6D6AFFFE5D5ACFFFFFFFFFFAE730DFFF6F0DEFFF1E8
      D1FFF0E6CDFFF0E7CDFFFFFFFFFFB47D1DFF008A47FF64E6D1FF60E2CBFF60E1
      CAFF60E1CAFF60E1CAFF60E1CAFF60E1CAFF60E1CAFF60E1CAFF60E0C8FF63DF
      C7FF00C49AFF00C59CFF86DEC8FF008A47FF8C9095FFF0C792FFD89E4CFFF1C8
      8EFFF1C98EFFD9A053FFD9A053FFF1C78CFFF0C281FFEBEFF4FFEBEAEBFFEBEA
      E9FFEBEAE9FFEBEAE9FFFCFBFBFF8B8C8CFFB16C13FFEEAD69FF7E959EFFCEF6
      FCFFCEF4F9FFD4FCFFFFB5D0D4FF594F4DFFADC5C8FFCEF4F9FFCDF2F7FFCEF6
      FCFF7E959EFFEEAD69FFB16C13FF00000000B47D1DFFFFFFFFFFF8F2E5FFF8F2
      E6FFF8F3E7FFF8F3E7FFF8F2E6FFF8F2E5FFFFFFFFFFAE730DFFF1EAD3FFF7F1
      E4FFFFFFFFFFFFFFFFFFFFFFFFFFB47E1DFF004223AF008A46FF008844FF0088
      43FF008843FF008843FF008843FF008843FF008843FF008743FF008640FF00AB
      7CFF00C09EFF9BE0D0FF008742FF000000008C8F92FFFFF3D5FFDCA251FFDBA4
      54FFF5CD91FFF5CE91FFDDA658FFDDA554FFF5CA87FFE2E5E9FFE3E2E2FFE3E2
      E1FFE2E1E0FFE3E2E1FFFCFBFBFF8C8C8CFFB16C13FFF1B172FFC7FAFFFFC9F3
      FBFFCDF6FDFFAECACEFF5D5250FFAEC9CEFFCCF6FCFFC8F0F6FFC7EEF4FFC8F1
      F9FFC7F9FFFFF1B172FFB16C13FF00000000B47D1DFFFFFFFFFFF3ECD9FFF3EC
      D9FFF3ECDAFFF3ECD9FFF3ECD9FFF3ECD8FFFFFFFFFFAE730DFFEFE4C7FFFFFF
      FFFFCFAB6CFFAC6F04FFFFFFFFFFB58021FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000089
      44FFA4E4D9FF008742FF00000000000000008D8F91FFFFFFEDFFFFF1CFFFF5D4
      A7FFF8DBB2FFFFF0CFFFFFF1D1FFF5D5A8FFF9DBAEFFF4F5F8FFF4F4F4FFF5F3
      F2FFF4F3F2FFF5F4F3FFFFFFFFFF8E8E8EFFA66613F8EBAD6CFFC8E9EBFFC4F4
      FFFFA9C8CCFF605551FFABC9CDFFC8F4FCFFC4EFF6FFC2ECF3FFC2ECF4FFC0EF
      F9FFC7E8EAFFEBAD6CFFA66613F800000000B47D1DFFFFFFFFFFF1E8CFFFF1E8
      D0FFF1E8D0FFF0E7CFFFF0E6CDFFF0E7CDFFFFFFFFFFAE730DFFEBDEBCFFFFFF
      FFFFAC6F04FFFFFFFFFFECDCC4FF523B11AC0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000033
      1B9A008C48FF000000000000000000000000808181EF8D8F91FF8C8E92FF8C8F
      93FF8C8F93FF8B8E92FF8B8E92FF8C8F93FF8C8E92FF8C8D8EFF8C8C8DFF8C8C
      8CFF8C8C8CFF8C8C8CFF8E8E8EFF808080EF3C250895D4934AFFE4CDA9FFBBF5
      FFFF5C514EFF95A8ADFFC2F2FAFFBEECF4FFBCEAF2FFBCE9F2FFBAEAF4FFB7EF
      FEFFE4CBA8FFD4934AFF3C25089500000000B47D1DFFFFFFFFFFEDE3C7FFEDE3
      C8FFEDE3C7FFF6F0E1FFFFFFFFFFFFFFFFFFFFFFFFFFB07510FFFFFFFFFFFFFF
      FFFFFFFFFFFFECDCC4FF4D360EA7000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B06A11FFEEB374FFD9DA
      C7FFB6F3FFFFB8EFFCFFB8ECF7FFB8EBF6FFB7EAF4FFB4E9F5FFB2ECFCFFD7D7
      C3FFEEB273FFB06A11FF0000000000000000B47D1DFFFFFFFFFFEBDDBCFFEBDD
      BDFFEBDCBBFFFFFFFFFFCFAB6CFFAC6F04FFFFFFFFFFB37C1BFFB58020FFB57E
      1FFFB58021FF523B11AC00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000D080146B56F18FFF1B6
      7AFFE6D3B2FFBCE5E9FFADECFFFF62808BFFADECFEFFBCE4E8FFE5D2B1FFF1B6
      79FFB56F18FF0D0801460000000000000000B57E1EFFFFFFFFFFE7D8B1FFE7D8
      B1FFE7D7B0FFFFFFFFFFAC6F04FFFFFFFFFFECDCC3FF4A350FA4000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000D080146B069
      10FFD99C54FFFAC18AFFFFCE9AFFFFCF9AFFFFCE9AFFFAC18AFFD99C54FFB069
      10FF0D080146000000000000000000000000B68123FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFECDCC4FF4D360EA700000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00003C250795A46511F7B06A10FFB06910FFB06A10FFA46511F73C2507950000
      000000000000000000000000000000000000A27627EFB68123FFB57E1EFFB47D
      1DFFB47D1DFFB47E1EFFB58021FF805A1BD50000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000001E00000031000000330000003300000033000000310000001E0000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000001E00000031000000330000003300000033000000310000001E0000
      0000000000000000000000000000000000000000002300000033000000330000
      0033000000330000003300000023000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000330000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000E0000
      0033333130AA797472F9817978FF817978FF817978FF797472F9333130AA0000
      00330000000E00000000000000000000000000000000000000000000000E0000
      003311174BAA2938B5F92A3ABEFF2A39BEFF2A3ABEFF2938B5F911174BAA0000
      00330000000E00000000000000000000000060564EC0B7A596FFB6A394FFB6A3
      94FFB6A394FFB7A596FF60564EC0000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0033008B4AFF00000033000000000000000000000000000000000000002D0000
      00330000002D000000000000000000000033000000000000000E0F0F0F6B847C
      7BFFC5B8BAFFF9E8ECFFFFF7FDFFFFF7FCFFFFF7FDFFF9E8ECFFC5B8BAFF847C
      7BFF0F0F0F6B0000000E0000000000000000000000000000000E0507166B2A3A
      BEFF495AE2FF6073FBFF677AFFFF6679FFFF677AFFFF6073FBFF495AE2FF2A3A
      BEFF0507166B0000000E0000000000000000B7A495FFE4D8CBFFE1D5C8FFE0D4
      C7FFE1D5C8FFE4D8CBFFB8A596FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000330087
      45FF00E9A8FF008745FF00000033000000000000000000000000090808E60A09
      09FF090808E60000000000000000090808FF000000000F0F0F6B8F8786FFE8D8
      DBFFA9E5D3FF17DDA3FF00D991FF00D992FF00D992FF1ADEA4FFAAE6D3FFE9D8
      DBFF8F8786FF0F0F0F6B0000000000000000000000000507166B2E3EC2FF586C
      F6FF6074FFFF5A6FFEFF5267FDFF4E64FDFF5267FDFF5A6FFEFF6074FFFF586C
      F6FF2E3EC2FF0507166B0000000000000000B5A293FFE9E1D7FFF2EAE1FFF1E9
      E0FFF2EAE1FFE9E1D7FFB8A494FF000000000000003300000033000000330000
      0033000000000000003300000033000000330000000000000033008745FF00E0
      A3FF00DC9FFF00E0A3FF008745FF0000003300000000000000001E1D1EFF0000
      00001E1E1EFF00000000000000331D1D1DFF0000001E8B8483FFE0CFD2FF6CDB
      BBFF00D690FF00D38EFF00D290FF00D494FF00D696FF00D696FF00D793FF6FDB
      BCFFE0CFD2FF8B8483FF0000001E000000000000001E2B3BBFFF5568F4FF5C70
      FCFF586CFAFF4C62F9FFA4AFF9FFFFFFFFFFA4AFF9FF4C62F9FF586CFAFF5C70
      FCFF5568F4FF2B3BBFFF0000001E00000000B5A191FFF2EDE5FFF8F3EFFFF7F2
      EDFFF8F3EFFFF2EDE5FFB8A393FF00000000737475FFB0B1B1FFAEAEAEFFB1B1
      B1FF00000000777777FFA2A2A2FFAEAEAEFF00000033008B4AFF00E2A9FF00D9
      9FFF00D69CFF00D99FFF00E2A9FF008D4BFF0000003300000000312D2EFF0000
      0033302F2FFF000000002E2D2DFF313030FF373634A9BBAEAFFF99D4C3FF00D1
      91FF00CC8CFFFFFFFFFFFFFFFFFF00CC8DFF00D096FF00D299FF00D298FF00D4
      96FF9CD4C4FFBBAEAFFF373634A90000000011174AA94255DEFF576CFBFF556A
      F8FF5267F7FF445BF6FFFFFFFFFFFFFFFFFFFFFFFFFF445BF6FF5267F7FF556A
      F8FF576CFBFF4255DEFF11174AA900000000B4A091FFFAF9F5FFFFFEFEFFFEFD
      FCFFFFFEFEFFFAF9F5FFB6A292FF000000000000000000000000000000000000
      000000000000000000000000000000000000008F4EFF008C4BFF008543FF09D8
      A4FF00D39BFF09D8A4FF008543FF008E4BFF009850FF00000000353132DD4644
      44FF403E3EF30000000000000000484646FF8B8684F9D3C2C5FF0DCE9DFF00C9
      8CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00C98DFF00CD96FF00CF99FF00D0
      98FF16D0A0FFD5C2C5FF8B8684F9000000002A3AB5F94E63F4FF5067F7FF4F65
      F5FF4D63F5FF4159F4FFA4AFF9FFFFFFFFFFA4AFF9FF4159F4FF4D63F5FF4F65
      F5FF5067F7FF4E63F4FF2A3AB5F900000000B5A292FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFB6A393FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008745FF14D9
      AAFF00CF9BFF14D9AAFF008745FF000000000000000000000000000000000000
      0033000000000000002C000000330000002D948E8DFFD4C0C3FF00C98FFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00C48DFF00C995FF00CB
      98FF00CD97FFD6C0C4FF948E8DFF000000002C3BBFFF4D64F8FF4B61F4FF4B61
      F3FF4A60F3FF445BF3FF364FF2FF2F48F1FF364FF2FF445BF3FF4A60F3FF4B61
      F3FF4B61F4FF4D64F8FF2C3BBFFF000000009D8E81ECB5A292FFB4A08FFFB39F
      8FFFB4A08FFFB5A292FF9D8E81EC000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008845FF20D9
      AFFF00CC9AFF20D9AFFF008845FF000000000000000000000000000000000403
      03FF00000000080707E4080707FF060505E5989291FFD0BABCFF00C691FFFFFF
      FFFFFFFFFFFF00C08BFF00BF8BFFFFFFFFFFFFFFFFFFFFFFFFFF00C18EFF00C6
      96FF00CA97FFD2BBBDFF989291FF000000002B3ABFFF5E73F7FF445CF2FF465D
      F1FF455CF1FF3F57F1FF6E81F3FFFFFFFFFF6E81F3FF3F57F1FF455CF1FF465D
      F1FF445CF2FF5E73F7FF2B3ABFFF000000000000002300000033000000330000
      0033000000330000003300000023000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008845FF2ED9
      B5FF00C99AFF2ED9B5FF008945FF000000000000000000000000000000331C1C
      1CFF000000001E1E1EFF000000001D1E1EFF999392FFDCC6C9FF00C394FF00C0
      93FF00C093FF00C196FF00C196FF00BC8EFFFFFFFFFFFFFFFFFFFFFFFFFF00BC
      8DFF00C293FFDCC6C9FF999392FF000000002939BFFF6F84F7FF3E57EFFF405A
      EFFF3F58EFFF3650EEFFA3AFF7FFFFFFFFFFA3AFF7FF3650EEFF3F58EFFF405A
      EFFF3E57EFFF6F84F7FF2939BFFF000000005C534BBDB7A596FFB6A495FFB6A4
      95FFB6A495FFB7A596FF5C534CBD000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008844FF3BD9
      BBFF00C69AFF3BD9BBFF008945FF0000000000000000000000002F2D2DFF3130
      30FF00000000302F2FFF00000033302F2FFF938E8CF8DECDCEFF15C3A1FF00BF
      98FF00C099FF00C19AFF00C19AFF00BE97FF00B98EFFFFFFFFFFFFFFFFFFFFFF
      FFFF03BE9AFFDCCCCCFF938E8CF8000000002736B5F893A1F4FF3650EEFF3A54
      EDFF3A54EDFF2D48EBFFDADFFBFFFFFFFFFFDADFFBFF2D48EBFF3A54EDFF3A54
      EDFF3650EEFF93A1F4FF2736B5F800000000B7A595FFE4D9CDFFE2D8CCFFE3D9
      CEFFE2D8CCFFE4D9CDFFB8A596FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008844FF47D9
      C0FF00C299FF47D9C0FF008944FF000000000000000000000000000000004A47
      47FF000000003F3D3DF2464444FF353333DF36343395C7BCBDFFA1D5CAFF00BC
      95FF00BD99FF00BE9AFF00BE9BFF00BE9AFF00BB96FF00B68EFFFFFFFFFFFFFF
      FFFF8ED0C3FFC4BBBCFF36343395000000000E134195838EE2FF697EF2FF304C
      EAFF324DE9FF2541E8FFFFFFFFFFFFFFFFFFFFFFFFFF2541E8FF324DE9FF304C
      EAFF697EF2FF838EE2FF0E13419500000000B6A394FFEBE4DCFFF7F3EFFFB06F
      21FFF7F4F0FFECE6DFFFB8A596FF000000000000003300000033000000330000
      0033000000000000003300000033000000330000000000000000008843FF53DB
      C4FF00BF98FF53DBC4FF008944FF0000000000000000000000000000002D0000
      00330000002D00000000000000000000003300000000A19B99FFEDDCDEFF73D1
      C2FF00B696FF00B899FF00B89AFF00B99AFF00B899FF00B595FF00B18EFF60CC
      BBFFE5DADBFFA09A99FF0000000000000000000000002E3EC2FFADB7F5FF6579
      F0FF2744E7FF1E3CE6FFBCC4FBFFFFFFFFFFBCC4FBFF1E3CE6FF2744E7FF6579
      F0FFADB7F5FF2E3EC2FF0000000000000000B5A293FFF4F1ECFFAD6B1BFFFEFF
      FFFFAE6E20FFE6D7C1FFBAA899FF00000000737475FFB0B1B1FFAEAEAEFFB1B1
      B1FF00000000777777FFA2A2A2FFAEAEAEFF0000000000000000008843FF60DC
      C9FF00BC98FF60DCC9FF008A44FF000000000000000000000000080707E60706
      06FF070606E50000000000000000040303FF000000001414145BAAA2A0FFF5E5
      E7FFAFE2DAFF19BEA6FF00B194FF00B294FF00B194FF18BEA6FFADE1D9FFF2E5
      E6FFA8A2A0FF0C0C0C4600000000000000000000000003040E463E4DC8FFA0AC
      F1FF8D9CF4FF4961EAFF1C39E5FF1130E3FF1C39E5FF4961EAFF8D9CF4FFA0AC
      F1FF3E4DC8FF03040E460000000000000000B4A191FFFCFBF9FFFFFFFFFFFFFF
      FFFFFFFFFFFFB27122FFB9A799FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008843FF6CDC
      CEFF00B898FF6CDCCEFF008A44FF0000000000000000000000001E1E1EFF0000
      00001E1E1EFF00000000000000331C1C1CFF00000000000000001514145BA59F
      9DFFD9CFCFFFFFF4F6FFFFFFFFFFFFFFFFFFFFFFFFFFFFF4F6FFD9CFCFFFA59F
      9DFF0C0C0C46000000000000000000000000000000000000000003040E462E3F
      C2FF6976DCFF9EAAF2FFADB9F8FFADB8F8FFADB9F8FF9EAAF2FF6976DCFF2E3F
      C2FF03040E46000000000000000000000000B5A292FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFB7A596FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008842FF78DF
      D4FF00B597FF78DFD4FF008A43FF000000000000000000000000302F2FFF0000
      0033302F2FFF000000002E2D2DFF302F2FFF0000000000000000000000000000
      0000393737959E9897F7A8A2A0FFA8A1A0FFA8A2A0FF9E9897F7393737950000
      0000000000000000000000000000000000000000000000000000000000000000
      00000E1341952534B4F72636BFFF2636BFFF2636BFFF2534B4F70E1341950000
      000000000000000000000000000000000000A19284EFB5A292FFB4A08FFFB39F
      8FFFB4A090FFB5A393FFA19285EF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008842FF86E0
      D9FF00B197FF86E0D9FF008943FF000000000000000000000000353333E04543
      43FF3F3D3DF50000000000000000474444FF424D3E000000000000003E000000
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
  object imgToolbar: TImageList
    ColorDepth = cd32Bit
    DrawingStyle = dsTransparent
    Left = 384
    Top = 288
    Bitmap = {
      494C010116001800040010001000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000006000000001002000000000000060
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      003300000033000000330000000B000000000000000000000000000000000000
      00000000001E00000031000000330000003300000033000000310000001E0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000334680
      ABFF477EAAFF4781ACFF050A0D5E0000000000000000000000000000000E0000
      0033473117AAAC7637F9B47B37FFB47B36FFB47B37FFAC7637F9473117AA0000
      00330000000E0000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      001A0000003100000033000000330000003300000030000000333D81B3FF729D
      BFFF1EADFFFF2B5367AD4391C6FF00000000000000000000000E150F076BB47B
      37FFDEC095FFFDF2DBFFFFFFF1FFFFFFF0FFFFFFF1FFFDF2DBFFDEC095FFB47B
      37FF150F076B0000000E00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000002E2727
      279C757372F97A7977FF7A7877FF7A7877FF716D6AF25A7C97FFA29A92FFAFA3
      9BFFA0C2D8FFB0ECFFFF3E90C6FF0000000000000000150F076BB98442FFF8EA
      D1FFFFFEEBFFFFF9E2FFFFF8E1FFFFF7E1FFFFF7E0FFFFF9E2FFFFFEEBFFF8EA
      D1FFB98442FF150F076B00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000002E696866EA9C9D
      9DFFD1D3D5FFE3E5EAFFE2E4E9FFE3E4E9FFD1D1D3FF9C9A9AFF83807CFFC6C2
      BDFFF4EBE4FFBFDEEAFF3E92CAFF000000000000001EB47B37FFF8EAD2FFFFF9
      E5FFFFF3DAFFFFF4DBFFFFF7DFFFFCEFD4FFFFF5DCFFFFF3D9FFFFF3D9FFFFF9
      E5FFF8EAD2FFB47B37FF0000001E000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000001A6A6968EAB4B3B6FFE6E4
      DFFFE9CD9AFFF1CB7DFFF5D489FFF9DB8DFFF2E1ADFFE6E5E0FFB0AEB0FF908B
      8AFFEDE3DBFF358FCAFF0000000000000000463217A9DEC098FFFFFBEAFFFDEF
      D3FFFDEED2FFFFF3D9FFCEA46EFFAD702AFFFFF8E0FFFEF1D6FFFDEED2FFFDEF
      D3FFFFFBEAFFDEC098FF463217A9000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000002929289BA2A1A2FFEBE6E2FFE9BB
      74FFEDC47CFFF3D28CFFF9DF98FFFBE69FFFFDE89EFFFBE39BFFEBE8E3FFA09C
      9CFF5A87A5FF000000000000000000000000AC7637F9FEF2E1FFFEEFD4FFFBEA
      CBFFFCECCDFFFFF3D6FFAF7531FFF5CB89FFAE732FFFFFF5DAFFFEEED0FFFCEB
      CCFFFEEFD4FFFEF2E1FFAC7637F9000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007E7B7AF9DCDFE1FFE6C28FFFEBC5
      8BFFF0D399FFF7DA95FF885825FFFFF2A9FFFFF4ABFFFDE89EFFF5E2AEFFDBDC
      DEFF777270F2000000000000000000000000B47B36FFFFFFFBFFFBE7C6FFFAE6
      C6FFFBE8C8FFFFEFD3FFB17835FFE2AF61FFE7BA76FFAF7531FFFFF0D4FFFCE9
      C9FFFBE7C6FFFFFFFBFFB47B36FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000858482FFF4F8FCFFE1A95DFFF5DE
      BAFFF8E1B5FFFFE9AFFF8F602CFFFFF5ACFFFFF2A9FFFBE59FFFF8D98CFFF3F4
      FAFF858382FF000000000000000000000000B47B36FFFFFFFCFFFAE2BEFFF9E2
      BFFFFAE4C2FFFFEBCDFFB27937FFD29E4EFFD19C4CFFD09A48FFAD712CFFFCE6
      C6FFFAE2BFFFFFFFFCFFB47B36FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000888584FFF7FCFFFFDFA558FFFAED
      D7FF89581FFF906028FF94652FFF8F602CFF885825FFF9DF98FFF4D287FFF5F9
      FFFF888584FF000000000000000000000000B47B36FFFFFFFFFFF7DFB8FFF7DF
      B9FFF8E1BCFFFDE8C5FFB27937FFC28A37FFDCBE8FFFB07633FFFDE9C7FFF9E1
      BDFFF8DFB8FFFFFFFFFFB47B36FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008A8886FFFDFFFFFFDC9F52FFF9EA
      D7FFFCEFD6FFFFEFCBFF906028FFFFE9AFFFF7DA95FFF2D28BFFEFC87BFFFBFD
      FFFF8A8786FF000000000000000000000000AA7736F8FEF4E8FFFAE2BFFFF6DA
      B2FFF7DCB5FFFBE2BDFFB17834FFE4D0B0FFB07632FFFCE4C1FFF8DEB8FFF6DB
      B3FFFAE2BFFFFEF4E8FFAA7736F8000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000858281F8EAEDF1FFE6BA88FFEDCC
      A3FFFBF4E7FFFCEED5FF89581EFFF8E1B4FFF1D29AFFEBC37AFFF0D3A1FFE9EB
      F0FF848280F80000000000000000000000003E2B1495DEC19EFFFFF5E8FFF5D7
      ABFFF5D8AEFFF8DDB5FFCC9E64FFAF7530FFFBE1BAFFF7DBB3FFF5D8AEFFF5D7
      ACFFFFF5E8FFDEC19EFF3E2B1495000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000026252583B3B2B2FFFEFAF5FFDBA0
      57FFECCCA3FFFBEFDFFFFAECD6FFF4E0BEFFECCA95FFE7B971FFFFFDF9FFB2B1
      B2FF2625258300000000000000000000000000000000B57C37FFF8ECE0FFFEEB
      D4FFF4D2A4FFF5D4A9FFF7D7ADFFF7D8AEFFF6D6ABFFF4D3A7FFF4D2A4FFFEEB
      D4FFF8ECE0FFB57C37FF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000767473E5CDCDCFFFFFFD
      FAFFE7BC8AFFDA9D50FFDDA356FFDEA65AFFECC896FFFFFFFCFFCCCCCEFF7673
      73E500000000000000000000000000000000000000000D090446B98542FFF8EC
      E3FFFFF3E6FFF7D9B2FFF3CF9FFFF3CF9FFFF3CF9FFFF6D9B1FFFFF3E6FFF8EC
      E3FFB98542FF0D09044600000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000777674E5B8B8
      B9FFF5F8FCFFFFFFFFFFFFFFFFFFFFFFFFFFF5F7FCFFB8B7B9FF777574E50000
      00000000000000000000000000000000000000000000000000000D090446B57C
      37FFDFC1A1FFFFF4F0FFFFFFFFFFFFFFFFFFFFFFFFFFFFF4F0FFDFC1A1FFB57C
      37FF0D0904460000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000002827
      26838C8989F7959391FF959291FF959291FF8C8989F728272683000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00003E2B1495A97535F7B47B36FFB47B36FFB47B36FFA97535F73E2B14950000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000230000
      0033000000330000002200000000000000000000000000000000000000000000
      0000000000220000003300000033000000230000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000003300000033000000330000000B0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      003300000033000000330000000B0000000000000000000000005F440EC0C18B
      25FFBF8A22FF5C420DBD00000021000000000000000000000000000000000000
      00225B410EBDC08B21FFC18C24FF5F440EC00000000000000000000000000000
      0000000000000000003300000033000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00334680ACFF477EAAFF4781ACFF050A0D5E0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000334680
      ABFF477EAAFF4781ACFF050A0D5E000000000000000000000000C28E29FFEEBB
      67FFE8AF4EFFD1972CFF583E09B900000021000000000000000000000023563E
      0DB9D0952AFFE7AB48FFEDB861FFC28E28FF0000000000000000000000000000
      000000000033008948FF008948FF000000330000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000001A0000003100000033000000330000003300000030000000333B81
      B5FF709EBFFF1EADFFFF2B5367AD4391C6FF0000000000000000000000000000
      001A0000003100000033000000330000003300000030000000333D81B3FF729D
      BFFF1EADFFFF2B5367AD4391C6FF000000000000000000000000C18E29FFFFF2
      D2FFE9B55DFFE7AC4AFFD6982DFF583E09B900000021000000005A410CB8D398
      2CFFE6A945FFE8B358FFFFF6D3FFC18E29FF0000000000000000000000000000
      0033008644FF0AE9ABFF0AE9ABFF008644FF0000003300000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      002E2727279C767372F97B7977FF7B7877FF7B7877FF706D6BF27C7775FF9F9A
      94FFAFA49BFFA0C2D8FFB0ECFFFF3E90C6FF00000000000000000000002E2727
      279C757372F97A7977FF7A7877FF7A7877FF716D6AF25A7C97FFA29A92FFAFA3
      9BFFA0C2D8FFB0ECFFFF3E90C6FF000000000000000000000000523B0AACCF9E
      41FFFFEFCCFFEEC476FFE6AC4AFFD5982EFF543B0BB50000002E4C3506ADE9AA
      42FFE9B256FFFFF3CEFFD5A653FF523B0AAC0000000000000000000000330086
      43FF0AE7A9FF00D89DFF00D89DFF0AE7A9FF008643FF00000033000000000000
      00000000000000000000000000000000000000000000000000000000002E6968
      66EA9E9D9DFFD1D3D5FFE3E5EAFFE2E4E9FFE3E4E9FFD0D1D4FF9C9B9BFF8480
      7DFFC5C0BEFFF4EBE4FFBEDEEAFF3E92CAFF000000000000002E696866EA9C9D
      9DFFD1D3D5FFE3E5EAFFE2E4E9FFE3E4E9FFD1D1D3FF9C9A9AFF83807CFFC6C2
      BDFFF4EBE4FFBFDEEAFF3E92CAFF000000000000000000000000000000004E36
      07A7DBAC55FFFFEECBFFE8B45CFFE7AD4AFFD6982CFF876625ED868D99E9D9B7
      7EFFFFF4CBFFDCAC54FF4E3708A8000000000000000000000033008643FF1CE9
      B0FF00D39DFF00D19AFF00D19AFF00D39DFF1CE9B0FF008643FF000000330000
      000000000000000000000000000000000000000000000000001A6A6968EAB3B3
      B6FFE6E4DFFFEACD9AFFF2CC7EFFF6D58AFFFADC8EFFF2E1ADFFE6E5E0FFB0AE
      B1FF908B8AFFEAE3DCFF358EC9FF020507320000001A6A6968EAB4B3B6FFE6E4
      DFFFE9CD9AFFF1CA7DFFF5D388FFF9DA8DFFF2E1ADFFE6E5E0FFB0AEB0FF908B
      8AFFEDE3DBFF358FCAFF00000000000000000000000000000000000000000000
      00004D3506A6E0B568FFFFEECBFFEAB45BFFEBAD43FF9C782FFFDDE1E9FFA0A3
      ACFB51401E9B523906AB000000000000000000000033008643FF2CEBB9FF00CF
      9CFF00CD9AFF00CC99FF00CC99FF00CD9AFF00CF9CFF2CEBB9FF008642FF0000
      003300000000000000000000000000000000000000002929289BA3A1A3FFEBE7
      E3FFE9BC75FFEFC880FFF8D891FFFEE59DFFFFEBA3FFFFEBA0FFFCE49BFFEAE8
      E4FFA09C9DFF968B83FF0104052A000000032929289BA2A1A2FFEBE6E2FFE9BB
      74FFECC47BFFF1D089FFF5DA94FFFAE39CFFFDE89EFFFBE39BFFEBE8E3FFA09C
      9CFF5A87A5FF0000000000000000000000000000000000000022000000330000
      0022000000004A3305A2DDAC53FFFFF0C7FFDFBD83FFB3B5BCFF7D7D7EFF3030
      32A700000033000000330000002600000000008947FF3BEFC4FF00C99BFF00C8
      99FF00C99AFF3BE9BDFF3BE9BDFF00C99AFF00C89AFF00CA9BFF3DEEC2FF0086
      42FF00000033000000000000000000000000000000007F7B7AF9DCDFE2FFE6C3
      91FFE8B971FFF1CC85FF744D20FF785024FF72481DFFFFF8AFFFFDE99EFFF5E2
      AEFFDADCDDFF7A706CF100000000000000007E7B7AF9DCDFE1FFE6C28FFFEBC5
      8BFFEFD298FFF2D48FFFF7DF9AFFFCEBA4FFFFF3AAFFFDE89EFFF5E2AEFFDBDC
      DEFF777270F200000000000000000000000000000022444342BD868484FF4041
      43BD000000060000001F85631DECA1792EFFE2E6EDFFC9C9CBFFA7A5A4FF7170
      6FFF8A8B8FFF7A7B81FF464648CB0000002F008946FF4DF0CDFF00C69BFF00C5
      9BFF4EEFCAFF00833FFF00833FFF4EEFCAFF00C69BFF00C59AFF00C69CFF4EF0
      CBFF008641FF00000033000000000000000000000000868482FFF4F8FDFFE1A9
      5EFFEFD2A2FFF2D59CFFFDE098FF795024FFFFF5ACFFFFEFA6FFFAE39DFFF7D9
      8BFFF3F4FAFF89837EFF0000000000000000858482FFF4F8FCFFE1A95DFFF5DE
      BAFFF7E0B3FFF9E2A9FFFDE59FFFFFEEA6FFFFF1A8FFFBE59FFFF8D98CFFF3F4
      FAFF858382FF000000000000000000000000454443BDA5A19FFFBFBDBBFFAFAE
      ADFF0404044C292A2DB0A3A5AAFFE0E2E7FF828080FFD1D0D0FFC9C7C6FFD3D1
      D1FFEBEBECFFEFEEF0FFDCDCDCFF706F6DF000000000008641FF5DF2D4FF5EF2
      D4FF008641FF0000000000000000008541FF5FF1D2FF00C19BFF00C09AFF00C2
      9BFF5FF2D2FF008641FF000000330000000000000000888584FFF7FCFFFFDEA5
      59FFF4E0C1FFF4D9AEFFFCE0A5FF764E21FFFEE69FFFF7E09BFFF4DA94FFF3D1
      86FFF5F9FFFF888583FF0000000000000000888584FFF7FCFFFFDFA558FFFAED
      D7FF88571EFF8B5B23FF8C5C26FF8B5B27FF885724FFF9DF98FFF4D287FFF5F9
      FFFF888584FF0000000000000000000000008A8987FFE0DEDEFFB9B7B5FFC3C1
      BFFF9F9C9BFF737270FFE7E7E7FFADAAA8FF83817EFFDBD9D8FFCECCCCFFCDCB
      C9FFCBC9CAFF898684FF878582FF8A8886FF0000000000000000008946FF0089
      46FF00000000000000000000000000000000008641FF71F3DBFF00BC9AFF00BC
      99FF00BD9BFF5EF2D2FF008641FF00000033000000008A8886FFFCFFFFFFDC9E
      51FFF8EAD8FFF7E2C1FFFEE6B9FF774F20FFF9DB96FFF3D48FFFF0CF89FFEEC8
      7BFFFBFDFFFF8A8786FF00000000000000008A8886FFFDFFFFFFDC9F52FFF9EA
      D7FFFBEDD4FFFBE8C4FFFBE5B6FFF9E2A8FFF6D993FFF2D28BFFEFC87BFFFBFD
      FFFF8A8786FF00000000000000000000000042413FB0A29F9CFFE3E3E2FFC4C2
      BFFFD4D2D1FFBBB9B8FF787674FF292928918B8987FFE1E1E0FFCAC8C7FFCCCA
      C9FF8E8C89FF0000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000008640FF83F4E4FF00B8
      9BFF00B79AFF00B79BFF6EF4DCFF008945FF00000000858281F8EBEDF1FFE5B8
      85FFF8EAD8FFFBEEDBFF734915FF754D1DFFF5D8A0FFEDC883FFEBC37BFFF0D3
      A1FFEAEBF0FF848280F80000000000000000858281F8EAEDF1FFE6BA88FFEDCC
      A3FFFAF3E6FFF7E8CEFFF5E1BCFFF3DAADFFF0D198FFEBC37AFFF0D3A1FFE9EB
      F0FF848280F80000000000000000000000000000000000000000908D8BFFEAE9
      EAFFD0CECDFFD4D2D2FF2F2E2D9F0000000093918EFFE3E2E1FFBBB9B8FFBCBA
      BAFF94928FFF0000003300000033000000330000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008640FF83F4
      E4FF00B29AFF00B29AFF81F5E5FF008945FF0000000026252583B2B2B2FFFDF9
      F3FFE1AE72FFFAECDAFFFEF1DEFFFAE6C7FFF2D6A9FFE6BA73FFE7BA73FFFFFD
      F9FFB2B1B2FF26252583000000000000000026252583B3B2B2FFFEFAF5FFDBA0
      57FFECCBA2FFF9ECDCFFF6E7D0FFF2DDBBFFECC995FFE7B971FFFFFDF9FFB2B1
      B2FF2625258300000000000000000000000000000000000000003B3938AAAEAC
      A9FFF2F1F1FFAEADABFF0000002D000000088E8D8AF4D5D4D3FFDDDBDBFFB4B1
      AFFFA9A6A4FF9D9B98FF9E9C98FF9C9B97FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000086
      40FF91F8EEFF91F8EEFF008640FF000000000000000000000000767473E5CCCC
      CEFFFFFCF7FFE6BB88FFE0AC69FFE3B272FFDFA75AFFECC997FFFFFFFDFFCCCC
      CEFF767373E500000000000000000000000000000000767473E5CDCDCFFFFFFD
      FAFFE7BC8AFFDA9C50FFDDA255FFDEA659FFECC896FFFFFFFCFFCCCCCEFF7673
      73E5000000000000000000000000000000000000000000000000000000003836
      35A8B5B3B2FFFFFEFEFF6C6B6AE6060606530B0B0A52AFADABFFDBDAD9FFF0EE
      EFFFECEBEAFFE2E0E0FFBFBCBCFFA3A19EFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008945FF008945FF00000000000000000000000000000000000000007775
      74E5B8B7B8FFF5F7FBFFFFFFFFFFFFFFFFFFFFFFFFFFF5F7FCFFB8B7B9FF7775
      74E5000000000000000000000000000000000000000000000000777674E5B8B8
      B9FFF5F8FCFFFFFFFFFFFFFFFFFFFFFFFFFFF5F7FCFFB8B7B9FF777574E50000
      0000000000000000000000000000000000000000000000000000000000000000
      000022212084B2B0AFFFB6B4B3FF8A8887FF393837B10404042B848280E4AEAC
      A9FFB9B6B5FFABA9A5FF72706DD2030303230000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000282726838C8989F7959291FF959291FF959291FF8C8989F7282726830000
      0000000000000000000000000000000000000000000000000000000000002827
      26838C8989F7959391FF959291FF959291FF8C8989F728272683000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000002300000033000000330000003300000023000000000000
      0023000000330000003300000033000000230000000000000000000000000000
      00000000001E00000031000000330000003300000033000000310000001E0000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000001E00000031000000330000003300000033000000310000001E0000
      0000000000000000000000000000000000000000003000000033000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      0033000000330000002F00000000000000000000000000000000000000000000
      0000000000003F3C3AC06F6D6BFF696664FF666262FF2F2F2DBD000000003C3B
      3ABD6F6D6BFF6A6666FF666262FF333130C000000000000000000000000E0000
      0033442308AAA55513F9AD5811FFAD5811FFAD5811FFA55513F9442308AA0000
      00330000000E00000000000000000000000000000000000000000000000E0000
      0033442308AAA55513F9AD5811FFAD5811FFAD5811FFA55513F9442308AA0000
      00330000000E0000000000000000000000003D89BCF24298D2FF3F94D0FF3D92
      CFFF3D92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92CEFF3E92
      CEFF3E93CFFF3983B6F00000000E00000000000000000000000B0000000A0000
      000A000000077A716AFFC4C2BFFFBDBCBAFF858482FF5E5A5AFF000000337774
      72FFC3C3C1FFBDBCBAFF858482FF605D5CFF000000000000000E140A026BAD59
      12FFCA8A47FFE0AD6DFFE6B87BFFE6B77AFFE6B87BFFE0AD6DFFCA8A47FFAD59
      12FF140A026B0000000E0000000000000000000000000000000E140A026BAD59
      12FFCA8947FFE0AD6DFFE6B77AFFE6B779FFE6B77AFFE0AD6DFFCA8947FFAD59
      12FF140A026B0000000E00000000000000004399D2FF3E94D0FFABFBFFFF9BF3
      FFFF92F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1FFFF93F1
      FFFFA6F8FFFF64B8E3FF060F155F000000000000002F050C105F050B0F5C040A
      0D590206084E796E66FFBFBDBAFFB7B6B4FF80807CFF5B5757FF6D6B68FF7471
      6FFFBEBDBBFFB7B6B4FF81807DFF5E5B5AFF00000000140A026BB15F18FFDAA4
      63FFE2B172FFE0AE6EFFDEAB69FFDDA865FFDEAB69FFE0AE6EFFE2B172FFDAA4
      63FFB15F18FF140A026B000000000000000000000000140A026BB15F18FFDAA4
      63FFE1B171FFDFAC6AFFDCA662FFDCA55FFFDCA662FFDFAC6BFFE1B171FFDAA4
      63FFB15F18FF140A026B00000000000000004298D2FF4EA6D9FF8EDAF5FFA2EE
      FFFF82E5FEFF84E5FEFF84E5FEFF85E6FEFF85E6FEFF85E6FEFF85E6FEFF84E6
      FEFF96EBFFFF8CD8F5FF1D4562B8000000003D88BAF14298D2FF3F94D0FF3D93
      D0FF3996D8FF786C64FFE5E3E1FFDFDEDDFFBDBCBCFF585351FFBBB7B6FF716E
      6BFFE4E2E1FFE0DFDEFFBFBFBEFF5E5B5AFF0000001EAE5A13FFD89F5DFFDFAC
      6AFFDDA967FFDCA763FFDAA25CFFFFFFFFFFDAA25CFFDCA763FFDDA967FFDFAC
      6AFFD89F5DFFAE5A13FF0000001E000000000000001EAE5A13FFD89F5DFFDFAC
      6AFFDDA865FFECD0B0FFFFFFFFFFFFFFFFFFFFFFFFFFDAA35DFFDDA865FFDFAC
      6AFFD89F5DFFAE5A13FF0000001E000000004196D1FF6ABEE8FF6CBDE6FFBBF2
      FFFF74DEFDFF76DEFCFF77DEFCFF7ADFFCFF7CDFFCFF7CDFFCFF7CDFFCFF7BDF
      FCFF80E0FDFFADF0FFFF4C9DD3FF0000000E4399D2FF3E94D0FFABFBFFFF9BF4
      FFFF91F7FFFF786760FF6B6562FF625F5CFF5E5958FF6B98A1FFB9B4B2FF79A7
      B0FF696563FF646160FF635F5DFF615D5BFF432408A9C5823DFFDCA765FFDAA3
      61FFD9A25FFFD8A15DFFD69C55FFFFFFFFFFD69C55FFD8A15DFFD9A25FFFDAA3
      61FFDCA765FFC5823DFF432408A900000000432408A9C5823DFFDCA765FFDAA3
      61FFD9A15DFFD69C54FFECD0B0FFFFFFFFFFD4954AFFD79F59FFD9A25FFFDAA3
      61FFDCA765FFC5823DFF432408A9000000003F95D0FF8AD7F5FF43A1D8FFDDFD
      FFFFDAFAFFFFDBFAFFFFDEFAFFFF73DCFCFF75DBFAFF74DAFAFF73DAFAFF73DA
      FAFF71D9FAFFA1E8FFFF7BBFE6FF060F155E4297D1FF55ACDDFF8EDAF5FFA2EE
      FFFF82E9FFFF84F3FFFF766965FFCBC7C4FF999694FF5B5352FFBBB6B3FF746E
      6BFFCAC7C4FF9B9795FF615A56FF00000000A65614F9D59C57FFD9A05BFFD79E
      59FFD79E59FFD79D57FFD59951FFD39549FFD4984EFFD69C56FFD79E59FFD79E
      59FFD9A05BFFD59C57FFA65614F900000000A65614F9D59C57FFD9A05BFFD79E
      59FFD79D57FFD5984EFFECCFAFFFFFFFFFFFD39448FFD69C56FFD79E59FFD79E
      59FFD9A05BFFD59C57FFA65614F9000000003D94D0FFABF0FFFF439DD6FF358C
      CBFF358CCBFF358CCBFF368BCBFF5BBEEAFF6ED9FBFF69D6FAFF67D5F9FF66D4
      F9FF65D4F9FF82DEFCFFAAE0F6FF1D4563B94196D1FF70C4EAFF6BBCE6FFBBF2
      FFFF74DFFEFF76E5FFFF7399A3FF6B6561FF645E5CFF6A96A2FF6D635FFF77A4
      B0FF6C6865FF67605CFF557388FF00000012AF5A14FFD79F59FFD49A54FFD499
      53FFD49953FFD49851FFD19348FFFFFFFFFFDDB079FFD19349FFD39751FFD499
      53FFD49A54FFD79F59FFAF5A14FF00000000AF5A14FFD79F59FFD49A54FFD499
      53FFD49851FFD19348FFEBCDACFFFFFFFFFFD08F42FFD39750FFD49953FFD499
      53FFD49A54FFD79F59FFAF5A14FF000000003C92CFFFB9F4FFFF72DBFBFF6ACC
      F2FF6BCDF3FF6BCEF3FF6CCEF3FF469CD4FF55BAE9FFDAF8FFFFD7F6FFFFD6F6
      FFFFD5F6FFFFD5F7FFFFDBFCFFFF3D94D0FF3F95D0FF90DDF8FF43A0D8FFDDFC
      FFFFDAFAFFFFDBFDFFFFDCFFFFFF766C67FFB9B5B1FF5F544FFF74F2FFFF776C
      67FFB8B4B0FF5E554FFF7DCDF9FF09172171AE5A13FFDAA768FFD2954CFFD295
      4CFFD2954CFFD1934AFFCF8F43FFEED7BDFFFFFFFFFFD9A466FFD09146FFD294
      4BFFD2954CFFDAA768FFAE5A13FF00000000AE5A13FFDAA768FFD2954CFFD295
      4DFFD2944BFFCF8E41FFE9CAA8FFFFFFFFFFCE8B3CFFD1934AFFD2954DFFD295
      4DFFD2954CFFDAA768FFAE5A13FF000000003B92CFFFC0F3FFFF70DAFBFF73DB
      FBFF74DBFCFF74DBFCFF75DCFCFF72DAFAFF439CD4FF368CCBFF358CCBFF348C
      CCFF338DCCFF3790CEFF3C94D0FF3881B3EB3D93CFFFB2F6FFFF50ACDEFF348A
      CAFF348ACAFF348CCCFF3491D4FF7B6A60FF6C5F58FF5D4D46FF67E5FFFF7466
      5FFF665C57FF5A4D45FFACE9FFFF235478C8AE5912FFDEAF77FFCE8E45FFCF8F
      46FFCD8D43FFCC8A3EFFCC893DFFCA8535FFF4E5D4FFFFFFFFFFCC883BFFCE8E
      45FFCE8E45FFDEAF77FFAE5912FF00000000AE5912FFDEAF77FFCE8E45FFCF90
      47FFCF8F46FFCC883CFFFFFFFFFFFFFFFFFFCB873AFFCE8E46FFCF9048FFCF90
      47FFCE8E45FFDEAF77FFAE5912FF000000003A92CFFFCAF6FFFF68D5F9FF6BD5
      F9FF6AD5F9FF68D5F9FF68D5FAFF69D7FBFF67D4FAFF5DC7F1FF5DC7F2FF5CC8
      F2FFB4E3F8FF3C94D0FF0A182169000000003C92CFFFB8F3FFFF76DFFEFF7AE0
      FEFF7BE1FEFF7BE1FFFF7BE4FFFF50B1E7FF54C2F5FFDAFFFFFFD6FCFFFFD5FE
      FFFFD5FFFFFFD6FFFFFFDCFFFFFF3D95D1FFA35511F8E4BE96FFCC893CFFCC89
      3DFFCA8435FFFFFFFFFFD0924CFFC8802FFFD19652FFFFFFFFFFC88231FFCC89
      3DFFCC893CFFE4BE96FFA35511F800000000A35511F8E4BE96FFCC893CFFCD8A
      40FFCD8B40FFCB873AFFC77E2CFFC77C2AFFCA8637FFCD8B40FFCD8C42FFCD8A
      40FFCC893CFFE4BE96FFA35511F8000000003A92CFFFD5F7FFFF5FD1F9FF60D0
      F8FFB4EBFDFFD9F6FFFFDAF8FFFFDAF8FFFFDBF9FFFFDCFAFFFFDCFAFFFFDCFB
      FFFFE0FFFFFF3D95D0FF02060833000000003B92CFFFC0F3FFFF6FD9FBFF72DA
      FBFF73DAFBFF73DAFBFF73DBFCFF75DEFFFF4EABDEFF358CCCFF348CCCFF328C
      CDFF328DCEFF3791D0FF3C94D0FF1F4661AE3B1F0695D5A67AFFD9A86EFFC883
      33FFC57D2BFFFFFFFFFFEDD9C1FFC1731CFFEDD8BFFFFFFFFFFFC57C2AFFC883
      33FFD9A86EFFD5A67AFF3B1F0695000000003B1F0695D5A67AFFD9A86EFFC884
      35FFC98638FFC78232FFE8CAA9FFFFFFFFFFC6802EFFC98639FFC98639FFC884
      35FFD9A86EFFD5A67AFF3B1F0695000000003C94D0FFDCFCFFFFD8F7FFFFD8F7
      FFFFDBFAFFFF348ECDFF3891CEFF3992CFFF3992CFFF3992CFFF3992CFFF3A92
      CFFF3C94D0FF2F6C95D700000000000000003A92CFFFCAF6FFFF68D5F9FF6BD5
      F9FF69D4F9FF68D4F9FF68D5F9FF69D6FAFF6AD8FBFF6AD9FCFF6ADAFDFF68DA
      FDFFDAFDFFFF3B93D0FF0104052F0000000000000000B15D18FFE8CBAEFFD7A1
      66FFC37723FFDBAF7EFFFFFFFFFFFFFFFFFFFFFFFFFFDBAF7EFFC37723FFD7A1
      66FFE8CBAEFFB15D18FF000000000000000000000000B15D18FFE8CBAEFFD7A2
      68FFC57C2CFFC57A29FFE7C8A7FFFFFFFFFFC37826FFC67D2EFFC67D2DFFD7A2
      68FFE8CBAEFFB15D18FF00000000000000001F4864B03C94D0FF3992CFFF3992
      CFFF3C94D0FF2C658DD200000000000000000000000000000000000000000000
      0000000000000000000000000000000000003A92CFFFD5F7FFFF5FD1F9FF60D0
      F8FFB4EBFDFFD9F6FFFFDAF8FFFFDAF8FFFFDAF9FFFFDBF9FFFFDAF9FFFFDAFA
      FFFFDFFEFFFF3C94D0FF0206093500000000000000000D070146B76B2BFFE4C3
      A0FFE0B98DFFCD8E47FFC0731EFFBF6D14FFC0731EFFCD8E47FFE0B98DFFE4C3
      A0FFB76B2BFF0D0701460000000000000000000000000D070146B76B2BFFE4C3
      A0FFE1BB90FFCE924DFFC27724FFC0701AFFC37929FFCF9350FFE1BB90FFE4C3
      A0FFB76B2BFF0D07014600000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003C94D0FFDCFCFFFFD8F7FFFFD8F7
      FFFFDBFAFFFF348ECDFF3891CEFF3992CFFF3992CFFF3992CFFF3992CFFF3992
      CFFF3C94D0FF377FB1EA000000000000000000000000000000000D070146B15D
      19FFCC935FFFE2C09CFFE9CEB0FFE9CDAFFFE9CEB0FFE2C09CFFCC935FFFB15D
      19FF0D07014600000000000000000000000000000000000000000D070146B15D
      19FFCC935FFFE2C09DFFEACFB0FFEACEB0FFEACFB1FFE2C09DFFCC935FFFB15D
      19FF0D0701460000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003A85B8EF3C94D0FF3992CFFF3992
      CFFF3C94D0FF3379A7E40104052B020508320205083302050833020508330206
      0833030709370000000000000000000000000000000000000000000000000000
      00003B1F0695A4520FF7AD570FFFAD570EFFAD570FFFA4520FF73B1F06950000
      0000000000000000000000000000000000000000000000000000000000000000
      00003B1F0695A4520FF7AD570FFFAD570EFFAD570FFFA4520FF73B1F06950000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000330000003300000014000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000002E000000330000003300000033000000330000
      0033000000330000003300000033000000300000002300000033000000330000
      0033000000330000003300000023000000000000000000000023000000330000
      0033000000330000003300000033000000230000000000000000000000000000
      0000B97A3CFFB0763EFF23170C84000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0033000000330000000000000000000000000000000000000000000000000000
      0033000000330000000000000000000000000000002300000033000000330000
      00330000003300000033A09C97ECB1B0AEFFAEAEABFFADADABFFADADABFFADAD
      ABFFADADABFFAEAEABFFAFAFADFF9F9F9DF23F3F3DC0757371FF6F6C6BFF6C69
      68FF686664FF656261FF333130C000000000000000003F3F3DC0757371FF6F6C
      6BFF6C6968FF686664FF656261FF333130C00000000000000000000000000000
      0000C1803BFF00000000B2763EFF000000000000000000000000000000000000
      0021000000330000002300000000000000000000000000000000000000332F3F
      C4FF2F3FC4FF0000003300000000000000000000000000000000000000332F3F
      C4FF2F3FC4FF00000033000000000000000021364CC03F6793FF3E6793FF3F67
      93FF3D6693FF325E8FFFBBB7B0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFB0B0ADFF797775FF817D7CFF9C9996FF8985
      83FF706E6BFF585655FF5F5C5BFF0000000000000000797775FF817D7CFF9C99
      96FF898583FF706E6BFF585655FF605D5CFF0000000000000000000000000000
      0000C98439FF00000010B97A3CFF0000000000000000000000000000002D5035
      1BB0B0763EFF573B20BE000000000000000000000000000000332F3FC4FF6B7D
      FCFF6B7DFCFF2F3FC4FF000000330000000000000000000000332F3FC4FF6B7D
      FCFF6B7DFCFF2F3FC4FF00000033000000003E6994FF558AB0FF4B82ABFF4C82
      ABFF4A81ABFF407AA8FFB9B4ADFFFFFFFFFFFDFDFDFFFFFFFFFFFFFFFFFFFFFF
      FFFFFEFEFEFFFCFCFCFFFFFFFFFFAEAEABFF767472FFCFCFCFFFD9D7D6FFD0CF
      CEFFC8C8C7FFC3C1C1FF5D5958FF0000000000000000767472FFD0CFCFFFD9D7
      D6FFD0CFCEFFC8C8C7FFC3C1C1FF5D5A59FF0000000000000000000000000000
      0000A0672BE01B120771C07E3BFF00000000000000000000002395622EE55839
      1CAF00000016A46C3AF60000000000000000000000002F3FC4FF7082FAFF586D
      F9FF586DF9FF7082FAFF2F3FC4FF00000033000000332F3FC4FF7082FAFF586D
      F9FF586DF9FF7082FAFF2F3FC4FF000000003E6995FF6494BBFF4B83AEFF4D83
      AEFF4B82AEFF417CACFFB8B3ACFFFFFFFFFFFBFBFAFF818181FFB5B5B6FFB4B4
      B4FFB1B1B1FFF9F9F8FFFFFFFFFFADADABFF757371FFB3B1AFFFCAC9C7FFB0AE
      ADFF91908EFF747371FF5D5958FF0000003300000033767472FFB3B1AFFFCAC9
      C7FFB0AEADFF91908EFF747471FF5E5B5AFF0000000000000000000000000000
      000004020126D08735FFC98234FF000000130000002164401DBDA26A30EB0000
      002B2B1C0E8B905F30E30000000000000000000000002F3FC4FF7587F8FF5368
      F7FF5368F7FF5368F7FF7587F8FF2F3FC4FF2F3FC4FF7587F8FF5368F7FF5368
      F7FF5368F7FF7587F8FF2F3FC4FF000000003E6A95FF73A1C3FF4E86B1FF5087
      B2FF4E86B2FF4481B0FFB8B2ABFFFFFFFFFFF6F6F5FFFBFBFAFFFBFBFAFFF9F9
      F8FFF7F7F6FFF4F4F3FFFFFFFFFFADADABFF757371FFB3B1AFFFCAC9C7FFB1AE
      AEFF939290FF767573FF5D5958FF797775FF63615FFF767472FFB3B1AFFFCAC9
      C7FFB1AEAEFF939290FF767573FF5F5C5BFF0000000000000000000000000000
      00000000000000000000B3906CFF1A1A1A7D603C16B5CC8537FFA16A2FE68A5A
      29D7BE7D3BFF00000000000000000000000000000000000000002F3FC4FF7A8C
      F7FF4E64F5FF4E64F5FF4E64F5FF7A8CF7FF7A8CF7FF4E64F5FF4E64F5FF4E64
      F5FF7A8CF7FF2F3FC4FF00000000000000003E6A97FF82ABCCFF4F88B5FF518A
      B6FF5089B6FF4684B5FFB8B2ABFFFFFFFFFFF3F2F2FF848484FFB2B2B3FFF5F4
      F4FFAEAEAEFFF1F0F0FFFFFFFFFFADADABFF757371FFB3B0AEFFCAC9C7FFB0AD
      ADFF91908EFF747371FF5A5756FF757371FF605E5CFF757371FFB3B1AFFFCAC9
      C7FFB0ADADFF91908EFF747472FF5E5B5AFF0000000000000000000000000000
      00000000000000000021AB8967FF9E958EFFE09B4CFF00000000000000000000
      0000000000000000000000000000000000000000000000000000000000002F3F
      C4FF8291F6FF4A60F3FF4A60F3FF4A60F3FF4A60F3FF4A60F3FF4A60F3FF8291
      F6FF2F3FC4FF0000000000000000000000003D6B97FF91B6D5FF518BBAFF548C
      BBFF538CBBFF4A88BBFFB8B2ABFFFFFFFFFFEEEDEDFFF3F2F2FFF3F2F2FFF1F0
      F0FFF0EFEFFFEDEBEBFFFFFFFFFFADADABFF767371FFDEDDDDFFEBEBE9FFDBDA
      D9FFCAC9C8FFBBBAB9FF565352FFD6D5D3FF8C8B89FF747270FFDEDDDCFFEBEB
      E9FFDBDAD9FFCAC9C8FFBCBCBBFF5D5A59FF0000000000000000000000000000
      0000000000224C4E51B6D37B1CFFB98B5DFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00002F3FC4FF8896F6FF455CF0FF455CF0FF455CF0FF455CF0FF8896F6FF2F3F
      C4FF000000000000000000000000000000003D6C97FF9FC1DDFF528EBDFF5691
      BFFF5591BFFF4C8CBFFFB7B1AAFFFFFFFFFFE9E9E8FF858585FFB2B1B1FFB0AF
      AFFFAEADADFFE8E8E6FFFFFFFFFFAEAEABFF797775FF6E6C6AFF656160FF5F5C
      5BFF5D5B59FF5D5959FF1A1A1A9BD3D2D0FF8A8987FF2423239B6B6967FF6360
      5FFF615E5DFF605E5CFF605D5CFF2A2828A80000000000000000000000000000
      002F515050B9ECEDEFFFBDB4A8FFCACCD0FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00332F3FC4FF8F9DF5FF4058EEFF4058EEFF4058EEFF4058EEFF8F9DF5FF2F3F
      C4FF000000330000000000000000000000003D6D99FFACCAE4FF5591C1FF5993
      C3FF5893C3FF4F8FC3FFB8B2AAFFFFFFFFFFE3E2E0FFE6E5E4FFE7E5E4FFE6E5
      E4FFE4E3E2FFE2E1E0FFFFFFFFFFAEAEACFF00000000767372FFBCBAB8FFCDCB
      CAFFA5A3A2FF7D7B7AFF585554FFD6D5D3FF8C8C89FF757271FFBCBAB7FFCCCA
      C9FFA4A2A1FF7D7B7AFF5E5B5AFF0000000000000000000000000000001B9391
      8EEDEBEBEBFF908F8FD3C4C3C3FFC7C6C6FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000332F3F
      C4FF97A3F5FF3B54ECFF3B54ECFF3B54ECFF3B54ECFF3B54ECFF3B54ECFF97A3
      F5FF2F3FC4FF0000003300000000000000003D6E9AFFB9D5EAFF5694C7FF5A97
      C8FF5A98C9FF5295CAFFBAB3ABFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFAFAFADFF00000000767372FFB9B7B5FFC9C7
      C6FFA2A09FFF7C7A79FF5B5757FF767371FF605E5CFF767372FFB9B8B5FFC9C7
      C6FFA2A09FFF7D7B7AFF5F5C5BFF0000000000000000000000003837379DEBEA
      EBFFAAA9A8E300000000CDCBCAFFC8C7C5FF0000000000000000000000000000
      00000000000000000000000000000000000000000000000000332F3FC4FF9EAB
      F4FF3650EAFF3650EAFF3650EAFF9EABF4FF9EABF4FF3650EAFF3650EAFF3650
      EAFF9EABF4FF2F3FC4FF00000033000000003C6F9AFFC6DEF0FF5697CCFF599A
      CFFF579AD1FF5298D2FF92AABEFFB5B2ADFFB2AFAAFFB2AEA9FFB3B0ABFFB1AF
      ACFFAFAEACFFAEAEACFFB0B0ADFF555553B000000000777473FFBDBBB9FFCECC
      CBFFA5A3A2FF7D7B7AFF5D5A59FF7A7876FF63615FFF787574FFBCBBB8FFCECC
      CBFFA6A4A3FF807D7CFF5F5C5BFF000000000000000000000000D4D4D3FFB9B8
      B7EB0000000000000000D4D2D1FFBDBBBAFF0000000000000000000000000000
      000000000000000000000000000000000000000000002F3FC4FFA7B3F5FF314C
      E7FF314CE7FF314CE7FFA7B3F5FF2F3FC4FF2F3FC4FFA7B3F5FF314CE7FF314C
      E7FF314CE7FFA7B3F5FF2F3FC4FF000000003D719DFFD4E7F7FF559BD3FFADA0
      96FFAA9F98FFA79E98FFA49E99FFA59D97FF4D98D5FFCCE4F8FF2E699AFF0000
      00000000000000000000000000000000000000000000383736AE706D6CFF6865
      64FF635F5EFF615D5CFF252423AA00000000000000002F2E2DAA6E6B6AFF6865
      64FF666362FF646160FF2E2C2CAE0000000000000000000000007E7D7CD30000
      00000000000000000000D9D7D6FFC2C2C0FF0000000000000000000000000000
      000000000000000000000000000000000000000000002F3FC4FFB0BBF5FF2C48
      E5FF2C48E5FFB0BBF5FF2F3FC4FF00000000000000002F3FC4FFB0BBF5FF2C48
      E5FF2C48E5FFB0BBF5FF2F3FC4FF0000000041749FFFAFD2F2FFA9D0F3FF978E
      87FFCECAC8FFCBC8C6FFCDCAC8FF968D87FFA8D0F4FFADD1F2FF3C729EFF0000
      0000000000000000000000000000000000000000000000000000000000337774
      73FFCBCAC7FF9B9A99FF615D5CFF0000000000000000777473FFCAC8C6FF9897
      96FF5F5C5BFF0000003300000000000000000000000000000000000000000000
      00000000000000000000D3D1D1FF949290EA0000000000000000000000000000
      00000000000000000000000000000000000000000000000000002F3FC4FFBAC3
      F6FFBAC3F6FF2F3FC4FF000000000000000000000000000000002F3FC4FFBAC3
      F6FFBAC3F6FF2F3FC4FF000000000000000021394DB04277A2FF3C76A4FF8880
      78FFB9B6B6FFB7B5B5FFB9B6B6FF888078FF3C76A4FF4277A2FF21394DB00000
      0000000000000000000000000000000000000000000000000000797875FF908D
      8CFF908E8CFF646360FF605D5CFF0000000000000000787674FF8E8B8AFF918F
      8DFF676563FF625F5EFF00000000000000000000000000000000000000000000
      00000000000000000000B6B4B2FC000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000002F3F
      C4FF2F3FC4FF0000000000000000000000000000000000000000000000002F3F
      C4FF2F3FC4FF0000000000000000000000000000000000000000000000000000
      0000807E7DFF7D7D7DFF807E7DFF000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007A7876FF7270
      6EFF6C6A68FF686564FF615E5DFF00000000000000007A7876FF72706EFF6C6A
      68FF686564FF625F5EFF00000000000000000000000000000000000000000000
      0000000000000000000000000033000000330000003300000000000000000000
      0000000000000000000000000000000000000000002300000033000000330000
      0033000000330000003300000033000000330000003300000033000000330000
      00330000003300000033000000330000002C0000001900000033000000330000
      0033000000330000003300000008000000080000003300000033000000330000
      0033000000330000003300000033000000190000000000000000000000000000
      0000000000000000000000000030000000330000003300000033000000330000
      0033000000330000003300000033000000300000000000000000000000240000
      00230000000000000000747270FF72706EFF747270FF00000000000000000000
      002F0000002300000000000000000000000060440CC0B67E0EFFB57C0AFFB57C
      0AFFB57C0AFFB57C09FFB47D09FFB47D08FFB47D08FFB47D07FFB57D07FFB67D
      06FFB77D06FFB77D08FFB77E0DFF8B6312E134250796B78217FFB68013FFB379
      05FFD7CFD2FFD8CEC9FF0B0B0A5309060053D9CFCEFFD5CAC3FFD4CAC4FFD6CF
      D2FFB37905FFB68013FFB78217FF342507960000000000000000000000000000
      000000000000000000009F9F9DF2B0B0AEFFAEAEACFFADADABFFADADABFFADAD
      ABFFADADABFFAEAEABFFAFAFADFF9F9F9DF200000000000000233D3D3BC13C3A
      3ABF0000002F00000033706E6CFFEEECEBFF706E6CFF00000033000000336765
      63F13C3C3BC0000000240000000000000000B67E0EFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFB77E0DFFB78217FFF6CD8BFFF2C67CFFF0C1
      70FFFAF7FBFFFFFFFFFF4B4747FF989392FFFFFFFFFFF7EFEAFFF6EFEBFFF9F6
      FAFFF0C170FFF2C67CFFF6CD8BFFB78217FF000000000000000B0000000A0000
      000A0000000A00000007B0B0AEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFB0B0ADFF000000003D3D3BBFA19F9DFF9E9C
      9AFF62605EEF706E6CFF898785FFE1DFDEFF898785FF706E6CFF716F6DFE9F9D
      9BFFA19F9DFF3E3C3BBD0000000000000000B57C0AFFFFFFFFFF882700FF9B43
      01FFA95919FFBD5D33FFFF0669FFFF146DFFFF11BDFFFF02B1FFA91ED7FF2D36
      FFFF191AFFFF0000FFFFFFFFFFFFB77C08FFB68115FFF3CA87FFEDBC6CFFEBB7
      60FFF8F5F7FFFFFFFFFF494440FF948C88FFFFFFFFFFF1E8E0FFF0E7E0FFF7F4
      F7FFEBB760FFEDBC6CFFF3CA87FFB68115FF0000002F0E0E0E5F0C0C0C5C0C0C
      0C5C0B0B0B590707074EB0B0ADFFF6F6F5FFECECEBFFFBFAFAFFFDFDFDFFFCFC
      FCFFFBFBFCFFFCFCFCFFFFFFFFFFAEAEABFF00000000686765ED9F9D9BFFDFDD
      DBFFB8B6B4FFDBD9D7FFD8D6D4FFD6D4D2FFD8D6D4FFDBD9D7FFB8B6B4FFDFDD
      DBFF9F9D9BFF393837AF0000000000000000B57C0AFFFFFFFFFFD8660CFFB365
      27FFB7723CFFC38A4EFFE57474FFFF5396FFFF56D1FFF252D1FF5D71FFFF5456
      FFFF3F44FFFF2246F9FFFFFFFFFFB77C06FFB68115FFF1CB89FFE9B761FFE7B2
      56FFF9F8FBFFFDF7F2FF877E78FF494340FFFEF7F2FFEEE3D8FFEDE2D9FFF8F7
      FBFFE8B256FFE9B761FFF1CB89FFB68115FF9D9D9BF1AFAFADFFAEAEABFFADAD
      ABFFADADABFFADADABFFACACAAFFA9A9A7FFA8A8A6FFB8B7B6FFFBFAFAFFF8F6
      F6FFF7F6F6FFF7F6F6FFFFFFFFFFADADABFF0000000000000000757471FEB7B3
      B3FFD2D0CFFFD1CFCFFFD3D1D0FFD3D1D0FFD3D1D0FFD1CFCFFFD2D0CFFFB7B3
      B3FF666462EF000000000000000000000000B47B0AFFFFFFFFFFFD8121FFFF9B
      4DFFE99C60FFD59A68FFDAAD75FFFD91A9FFFF8BE3FFA393FDFF7D88FFFF708A
      FAFF5B8AF2FF3168F5FFFFFFFFFFB77C06FFB68115FFF3CC8EFFE8B259FFE7AE
      50FFFCFFFFFFECE0D7FFF1E4DAFFF1E5DAFFEDE0D5FFEADDD3FFE9DED5FFFBFF
      FFFFE7AE50FFE8B259FFF3CC8EFFB68115FFB0B0ADFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA8A8A5FFF9F8F8FFF5F4
      F4FFF4F3F3FFF4F3F3FFFFFFFFFFADADABFF0000003300000033777573FFD2D0
      CEFFCECCCAFFBEBCBAFF92908EFF8D8B89FF92908EFFBEBCBAFFCECCCAFFD2D0
      CEFF777573FF000000330000003300000000B47B0AFFFFFFFFFFFE7C2AFFFF94
      55FFFFA673FFFFB78EFFFBBF9AFFFEC6A3FFE0BCFFFFA4B8FFFF92B0F9FF7D9D
      F6FF6387F3FF3B68F5FFFFFFFFFFB77B06FFB68114FFF3CE94FFE6AE50FFE5AB
      4AFFE6C9A4FFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFDFFFFFFFEFFFFFFE6C9
      A4FFE5AC4AFFE6AE50FFF3CE94FFB68114FFAEAEABFFFFFFFFFFFCFCFCFFFBFB
      FCFFFBFBFCFFFBFBFCFFFBFBFCFFFCFCFCFFFFFFFFFFA7A7A5FFF5F5F4FFF1F1
      F0FFEFEFEEFFEFEFEEFFFFFFFFFFADADABFF817E7CFF7B7977FF9D9B99FFCCC9
      C8FFCCC9C8FF93918FFF2D2C2B9C020202222D2C2B9C93918FFFCCC9C8FFCCC9
      C8FF9D9B99FF7B7977FF817E7CFF00000000B57A0AFFFFFFFFFFBDFF00FFC9FF
      32FFD5FF56FFDFFF75FFD9FF96FFCEFFB1FFBCF7FFFFA0E7FFFF7AD2FEFF5AC9
      FFFF38BFFFFF04ADFFFFFFFFFFFFB77B06FFB68114FFF3D09AFFE5A844FFE3A6
      3FFFE2A135FFE29E2EFFE19D2CFFE19D2BFFE19D2BFFE19D2CFFE29E2EFFE2A1
      35FFE3A63FFFE5A844FFF3D09AFFB68114FFADADABFFFFFFFFFFF7F6F6FFF7F6
      F6FFF7F6F6FFF7F6F6FFF7F6F6FFF7F6F6FFFFFFFFFFA7A7A5FFF1F1F1FFEDED
      ECFFEBEBEAFFEBEBEAFFFFFFFFFFADADABFF817E7CFFE3E1DFFFDCDAD8FFC6C5
      C2FFC8C6C4FF8F8D8BFF0404043D000000070404043D8F8D8BFFC8C6C4FFC6C5
      C2FFDCDAD8FFE3E1DFFF817E7CFF00000000B5790AFFFFFFFFFFC0FF00FFD0FF
      2AFFC1FF54FFAEFF72FFBBFF85FF8CFFB6FF8EF9FFFF9CECFFFF84E7FFFF5ECF
      FFFF2FB4FFFF00A6FFFFFFFFFFFFB87B06FFB68113FFF4D4A0FFE1A135FFF2DE
      B7FFFCFFFFFFFBFFFDFFFBFFFCFFFBFFFDFFFBFFFDFFFBFFFDFFFBFFFDFFFBFF
      FFFFF2DEB7FFE1A135FFF4D4A0FFB68113FFADADABFFFFFFFFFFF4F3F3FFF4F3
      F3FFF4F3F3FFF4F3F3FFF4F3F3FFF4F3F3FFFFFFFFFFA8A8A5FFEDECECFFF4F3
      F3FFFFFFFFFFFFFFFFFFFFFFFFFFAEAEABFF848280FF807D7BFF949492FFD0CE
      CCFFC3C0BFFF93918FFF343432AD0505054E343432AD939290FFC3C0BFFFD0CE
      CCFF949492FF807D7BFF848280FF00000000B5790AFFFFFFFFFF9FFF00FF89FF
      2FFF8FFF48FFA2FF59FF7CFF87FF4BFFADFF59FAFFFF6AEFFFFF70E4FFFF5AE3
      FFFF3EDAFFFF00B5FFFFFFFFFFFFB87A06FFB68013FFF6D8A7FFE09C26FFFBFF
      FFFFFCFBF3FFFCF9EFFFFBF8EEFFFCFAF0FFFCFAF0FFFBF9EEFFF9F8EDFFFAF9
      F1FFFAFEFEFFE09B26FFF6D8A7FFB68013FFADADABFFFFFFFFFFF0F0EFFFF0F0
      EFFFF0F0EFFFF0F0EFFFEFEFEEFFEFEFEEFFFFFFFFFFA8A8A5FFE9E8E7FFFFFF
      FFFFCACAC9FFA4A4A2FFFFFFFFFFAFAFADFF0000000000000000807D7BFFDAD9
      D8FFBEBBB9FFBCB9B7FF94918EFF928F8DFF94918FFFB3B2B0FFBEBBB9FFDBD9
      D8FF807D7BFF000000000000000000000000B57A09FFFFFFFFFF56FF00FF6AFF
      08FF7AFF1FFF77FF3EFF04FF90FF0FFF90FF1DF8FFFF0FF8FFFF3FE2FFFF32DA
      FFFF1AD8FFFF00D4FFFFFFFFFFFFB67A07FFB68013FFF8DCB0FFE0981BFFFBFB
      F8FF78777AFFA2A0A2FFFCF6EAFF787778FFA3A1A3FFA09FA1FFFAF4E9FF9D9D
      A0FFF9F9F6FFE0981BFFF8DCB0FFB68013FFADADABFFFFFFFFFFECECEBFFEDED
      ECFFEDEDECFFECECEBFFEBEBEAFFEBEBEAFFFFFFFFFFA8A8A5FFE4E4E3FFFFFF
      FFFFA4A4A2FFFFFFFFFFE9E9E9FF4F4F4EAC0000000000000023716F6DEFACAA
      A8FFC7C5C3FFBBB8B7FFBAB7B6FFBBB8B7FFBBB8B7FFBBB8B7FFC7C5C3FFACAA
      A8FF706F6DEF000000230000000000000000B57B0AFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFB57B09FFB68112FFFCE3BCFF9B6003FFFDFC
      F9FFFDF5E8FFFEF4E7FFFBF2E5FFFCF2E5FFFBF2E5FFFBF2E5FFFAF1E3FFF9F1
      E5FFFCFAF7FF9A6003FFFCE3BCFFB68112FFADADABFFFFFFFFFFE9E8E8FFEAE8
      E9FFE9E8E8FFF3F2F2FFFFFFFFFFFFFFFFFFFFFFFFFFA9A9A6FFFFFFFFFFFFFF
      FFFFFFFFFFFFE9E9E9FF4B4B49A70000000000000000454342BAA4A2A0FFDAD8
      D7FFC6C4C2FFE4E3E1FFDBD9D7FFC2BFBEFFD7D5D4FFE4E3E1FFC5C4C2FFDAD8
      D7FFA4A2A0FF454342BA0000000000000000B57D0EFFF8E0C0FFE1A54AFFE2A6
      4EFFE2A74FFFE2A74EFFE3A74DFFE3A74DFFE3A74CFFE3A74CFFE3A74CFFE3A7
      4CFFE3A74AFFE2A648FFF8E0BFFFB67D0EFFB68011FFFEE9C6FF704000FFFFFF
      FFFF787879FF797979FFA2A1A1FF9F9F9FFFF6ECDEFF767676FFA1A1A1FF9E9F
      A0FFFFFFFFFF6F4000FFFEE9C6FFB68011FFAEAEABFFFFFFFFFFE5E4E3FFE6E5
      E4FFE5E4E3FFFFFFFFFFCACAC9FFA4A4A2FFFFFFFFFFADADAAFFAFAFADFFAEAE
      ACFFAFAFADFF4F4F4EAC000000000000000000000000434241B2B2B1AFFFAFAE
      ACFF706F6DEB868482FF9A9897FFBCBAB7FF9A9897FF868482FF83817FFEAFAE
      ACFFB2B1AFFF434241B20000000000000000B68012FFF2D8AEFFD49221FFD494
      25FFD49426FFD49426FFD49426FFD49426FFD49426FFD49426FFD49426FFD494
      26FFD49425FFD49221FFF2D8AEFFB68012FFB68011FFFDECD1FFDA8600FFFFFF
      FFFFF1E5D8FFF2E5D8FFF2E5D7FFF0E3D6FFEFE2D5FFF1E4D7FFF1E4D6FFEFE3
      D6FFFFFFFFFFDA8600FFFDECD1FFB68011FFAEAEACFFFFFFFFFFE0E0DFFFE0E0
      DFFFE0E0DFFFFFFFFFFFA4A4A2FFFFFFFFFFE9E9E9FF484847A4000000000000
      0000000000000000000000000000000000000000000000000000444342B24240
      40AF00000000000000008B8987FFE9E7E7FF8B8987FF00000000000000007977
      74ED424241B0000000000000000000000000B88216FFEED09BFFECCE98FFECCE
      9AFFECCE9AFFECCE9AFFECCE9AFFECCE9AFFECCE9AFFECCE9AFFECCE9AFFECCE
      9AFFECCE9AFFECCE98FFEED09BFFB88216FFB78114FFFFECCDFFFCE7C3FFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFCE7C3FFFFECCDFFB78114FFAFAFADFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFE9E9E9FF4B4B49A700000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000908E8CFF8F8D8BFF908E8CFF00000000000000000000
      0000000000000000000000000000000000006F4F10C5B88216FFB78115FFB781
      15FFB78115FFB78115FFB78115FFB78115FFB78115FFB78115FFB78115FFB781
      15FFB78115FFB78115FFB88216FFA37418EF2B1E057CB78113FFB57D0EFFB57B
      0AFFB57B08FFB57B08FFB57B08FFB57B08FFB57B08FFB57B08FFB57B08FFB57B
      08FFB57B0AFFB57D0EFFB78113FF2B1E057C9D9D9BEFB0B0ADFFAEAEACFFAEAE
      ABFFADADABFFAEAEABFFAFAFADFF7B7B79D50000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0022000000330000003300000033000000330000003300000033000000330000
      0033000000330000003300000030000000000000000000000000000000000000
      0033000000270000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00060000002A000000330000001B000000000000000000000013000000330000
      002A0000000A0000000000000000000000000000000000000000000000000000
      0012000000330000003300000033000000330000003300000033000000330000
      0012000000000000000000000000000000000000000000000000000000330043
      23BB008947FF008846FF008846FF008846FF008846FF008846FF008846FF0088
      46FF008846FF008A48FF007D44F200000000000000000000000000000033008C
      4AFF00552ECD0000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000180105
      084C13629FDB1B8BE1FF0A2E4BA000000000000000000519297C1B8CE1FF1362
      9FDB020A105D000000130000000000000000000000000000000000000012080A
      217C2B3BC0FF2A3ABEFF2A39BEFF2A39BEFF2A39BEFF2A3ABEFF2B3BC0FF080A
      217C000000120000000000000000000000000000000000000033008946FF00B1
      73FF00D79CFF00DCA1FF00DCA0FF00DCA0FF00DCA0FF00DCA0FF00DCA0FF00DC
      A0FF00DCA1FF00E1A7FF008A48FF000000000000000000000033008744FF53D9
      B0FF008846FF0000003300000033000000330000003300000033000000330000
      0033000000220000000000000000000000000000000000000000072337872B9F
      E9FF42C4F9FF4BD0FDFF1A8AE1FF0000001000000003166FB5E841C0F6FF45C9
      FAFF37AAEEFF041A297E0000000000000000000000000000001207091F792E3D
      C3FF5E70F9FF687CFFFF687BFFFF687BFFFF687BFFFF687CFFFF5E70F9FF2E3D
      C3FF07091F790000001200000000000000000000001E008A46FF00C593FF00D0
      9FFF28D8AFFF5AE3C5FF5AE4C6FF5BE5C7FF5BE5C8FF5BE5C8FF5BE5C8FF5BE5
      C8FF5BE6C9FF5FEACEFF008A47FF0000000000000033008743FF64D7B3FF00D9
      A0FF00C384FF008543FF008745FF008846FF008846FF008846FF008846FF0089
      47FF004123B900000033000000000000000000000000000000000828418A47AF
      EEFF71DCFFFF47D0FFFF2BA4EBFF03121D6C000102271F91E4FF48D1FFFF63D7
      FFFF61C3F5FF187ECBF200000000000000000000001207091F792E3DC2FF586B
      F6FF6074FFFF5E73FEFF5E72FDFF5E72FDFF5E72FDFF5E73FEFF6074FFFF586B
      F6FF2E3DC2FF07091F79000000120000000000371DAA00A875FF00C5A1FF0CC8
      A6FF5FD6BCFF28AA77FF008641FF008743FF008743FF008743FF008743FF0087
      43FF008744FF008946FF004223B000000000008A47FF73DBBDFF00D09CFF00CE
      9AFF00D59CFF00D89FFF00D9A0FF00D9A0FF00D9A0FF00D9A0FF00D9A1FF00D7
      9CFF00B173FF008946FF0000003300000000000000000000000000000000136A
      B0E263C0F5FF5FD2FFFF39BBF9FF12619FDC0827419633B3F4FF4FCEFFFF7AD2
      FCFF156CB0E1000000000000000000000000080A217C2F3EC2FF5568F3FF5C70
      FCFF5A6EFAFF596DF9FF596DF9FF596DF9FF596DF9FF596DF9FF5A6EFAFF5C70
      FCFF5568F3FF2F3EC2FF080A217C00000000008344F900C19AFF00C6A0FF3FCA
      AAFF0D9255FF00160B6700000008000000000000000000000000000000000000
      000000000000000000000000000000000000008A47FF86E0C8FF00CB9BFF00C9
      99FF5EE3C3FF5BE5C6FF5BE6C7FF5BE6C8FF5BE6C7FF5AE5C6FF5AE4C5FF28D8
      AFFF00D09FFF00C593FF008A46FF0000001E0000001C0000002A000000250000
      00171563A0D977D0FCFF4DCBFFFF2196E8FF177FCDF540C4FEFF82D9FFFF1867
      A2D900000017000000250000002A0000001C2C3CC0FF5266F2FF566BFAFF546A
      F8FF5469F7FF5469F7FF5469F7FF5469F7FF5469F7FF5469F7FF5469F7FF556A
      F8FF566CFAFF5065F2FF2C3CC0FF00000000008946FF00CFA4FF00CDA1FF009D
      60FF000E07540000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000008742FF9BE3D0FF00C6
      9EFF00C28FFF008440FF008743FF008743FF008743FF008641FF28AA77FF5FD6
      BCFF0CC8A6FF00C5A1FF00A875FF00361DA90A304DA212639FDB0F4E7EC60723
      388F07263E95228FE1FF7DD5FFFF30AFF5FF23A1EFFF80D9FFFF2D9AE8FF0626
      3E950723388F0F4E7EC612639FDB0A304DA22A3ABFFF6175FCFF4F65F6FF4F65
      F5FF4F65F5FF4F65F5FF4F65F5FF4F65F5FF4F65F5FF4F65F5FF4F65F5FF4F65
      F5FF4F65F6FF5E74FCFF2B3ABFFF00000000008946FF00D6A3FF00D4A1FF0096
      55FF000201290000000000000000000000000000000000000000000000000000
      0023000000330000000000000000000000000000000000000000008742FFA4E6
      D9FF008844FF000000000000000000000000000000000000000800160B670D92
      55FF3FCAAAFF00C6A0FF00C19AFF008344F9198BE1FF6BC9FDFF2DB1F9FF27A4
      F0FF259FEEFF1C93E7FF329EE9FF72D0FFFF60C5FBFF44ABEEFF1B92E7FF259F
      EDFF27A3F0FF2DB1F9FF6AC9FCFF1A8EE3FF2939BFFF7286FAFF495FF4FF4B61
      F3FF4B61F3FF4B61F3FF4B61F3FF4B61F3FF4B61F3FF4B61F3FF4B61F3FF4B61
      F3FF495FF4FF6D81FAFF2A39BFFF00000000008846FF00DAA3FF00D8A0FF00A0
      60FF001C0F85000000100000000A000000000000000000000000000000000049
      28C1008C4AFF000000330000000000000000000000000000000000000000008B
      48FF004F2AC00000000000000000000000000000000000000000000000000016
      0B68009D60FF00CDA1FF00CFA4FF008946FF178AE1FF82D7FFFF2BB7FFFF2EB8
      FFFF4BC2FFFF52C5FFFF62CAFFFF8BD6FFFF9EDDFFFF61C9FFFF51C4FFFF4BC3
      FFFF2EB8FFFF2BB7FFFF81D5FFFF1C95E9FF2838BFFF8696FBFF4259F1FF455C
      F1FF465DF1FF465DF1FF465DF1FF465DF1FF465DF1FF465DF1FF465DF1FF455C
      F1FF425AF1FF7C90F9FF2938BFFF00000000008043F800D197FF00D99FFF00CB
      90FF008D4AFF00130A74000A055C000000330000003300000033000000330089
      46FF53D9B0FF008845FF00000033000000000000000000000000000000000000
      0002000000030000000000000000000000000000000000000000000000000002
      0129009655FF00D4A1FF00D6A3FF008946FF188BE1FF91D6FFFF6EC4FAFF64B9
      F4FF5BB4F1FF379DE7FF2599EAFF79CFFFFF78C9FCFF27A1F0FF379CE7FF53AF
      EFFF5BB4F1FF76C6FAFF8FD5FFFF329DE9FF2636BFFF9AA8FBFF3A54EFFF3F59
      EFFF415AEFFF415AEFFF415AEFFF415AEFFF415AEFFF415AEFFF415AEFFF3F59
      EFFF3B55EFFF8E9DFAFF2737BFFF00000000003019962EBD8BFF1FDEADFF00D5
      9DFF00C78FFF009F5FFF008743FF008845FF008845FF008845FF008642FF00BA
      7DFF00D8A0FF64D7B3FF008743FF000000330000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000010001C
      0F8500A060FF00D8A0FF00DAA3FF008846FF0829428B115D98D20C4775B8041C
      2D7306253D91188BE1FF2FB0FFFF69BBF5FF56B1F0FF48BCFFFF188EE5FF0B3D
      65B4041B2C720C4673B7105D98D20829428B2536BFFFCED6FFFF324DEDFF3A53
      EDFF3D56EDFF3D56EDFF3D56EDFF3D56EDFF3D56EDFF3D56EDFF3D56EDFF3A53
      EDFF324DEDFFC6CFFEFF2636BFFF0000000000000000008845FF39D1ABFF51E1
      C2FF1CD5ABFF0FD4A8FF10D5AAFF10D6ABFF10D6ABFF10D6ABFF10D5A9FF12D3
      A8FF00CC9BFF00CE9DFF73DBBFFF008A47FF0000000000000023000000330000
      003300000033000000330000003300000033000000330000003300130A74008D
      4AFF00CB90FF00D99FFF00D197FF008043F80000000000000000000000000000
      002D1465A2DD1CA3FBFF72CBFFFF277AB6E3125A91CF86D1FFFF1DA6FFFF1B8B
      DDFD0001023D0000000600000000000000002737C1FF9FABF1FF8393F4FF2F4A
      E9FF3550EAFF3752EAFF3852EAFF3852EAFF3852EAFF3752EAFF3550EAFF2F4A
      E9FF8393F4FF9FABF1FF2737C1FF000000000000000000000000008844FF39BA
      91FF61DEC8FF60E0CAFF61E0CAFF61E0CAFF61E0CAFF61E0CAFF61E0C9FF64DE
      C7FF00C59AFF00C69CFF86DEC8FF008A47FF00000000004827C0008A48FF0088
      45FF008845FF008845FF008845FF008845FF008845FF008743FF009F5FFF00C7
      8FFF00D59DFF1FDEADFF2EBD8BFF002F1995000000000000000000000027166F
      B3E71B99F2FF21A6FFFF7EC7FDFF05253C88041A2A7173BEF7FF29A9FFFF1A9D
      F9FF1C8CE0FF0004074A00000000000000000507185B2D3DC3FF99A6F0FF7E91
      F3FF2A46E7FF2F4BE8FF314CE8FF314CE8FF314CE8FF2F4BE8FF2A46E7FF7E91
      F3FF99A6F0FF2D3DC3FF0507185B00000000000000000000000000000000003D
      20AA008945FF008843FF008743FF008743FF008743FF008743FF008640FF00AB
      7CFF00BF9EFF9BDFD0FF008742FF0000000000000000008A48FF13DFB0FF10DA
      ABFF10DAAAFF10DAAAFF10DAAAFF10DAAAFF10DAAAFF10D9A9FF0FD4A9FF1CD5
      ABFF51E1C2FF39D1ABFF008845FF00000000000000000000000012578CCD2C9B
      EDFF1BA2FFFF4AB6FFFF4FAAEEFF01070C3D000001133299E5FF73C6FFFF1AA1
      FFFF35A4F5FF1C8DE2FF000000000000000000000000050717582E3EC2FF97A4
      EEFF7A8DF1FF223FE5FF2441E5FF2541E5FF2441E5FF223FE5FF7A8DF1FF97A4
      EEFF2E3EC2FF0507175800000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000089
      44FFA4E4D9FF008742FF000000000000000000000000008A46FF65E2D0FF61DD
      CAFF61DDC8FF61DDC8FF61DDC8FF61DDC8FF61DDC8FF61DDC9FF60E0CAFF61DE
      C8FF39BA91FF008844FF000000000000000000000000000000000D446EB249A7
      ECFF96D1FFFFA0D8FFFF158AE0FF00000000000000001680D0F681C6FBFF96D3
      FFFF47A9F3FF187BC5EE00000000000000000000000000000000050717582E3D
      C3FF95A1EFFFAEB9F8FFADB9F7FFADB9F7FFADB9F7FFAEB9F8FF95A1EFFF2E3D
      C3FF050717580000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000043
      24B1008C48FF00000000000000000000000000000000004223B000965CFF0093
      59FF009358FF009358FF009358FF009358FF009358FF009459FF008742FF0089
      44FF003B1FA80000000000000000000000000000000000000000000000000311
      1C5B1584D6F9349BE7FF0F5387C500000000000000000D436DB12B95E6FF158C
      E3FF0519296E0000000000000000000000000000000000000000000000000507
      185B2F3EC4FF4454CEFF4353CDFF4253CDFF4353CDFF4454CEFF2F3EC4FF0507
      185B00000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000600000000100010000000000000300000000000000000000
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
      000000000000}
  end
end
