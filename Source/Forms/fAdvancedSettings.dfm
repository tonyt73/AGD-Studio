object frmAdvancedSettings: TfrmAdvancedSettings
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Settings'
  ClientHeight = 457
  ClientWidth = 794
  Color = clBtnFace
  Constraints.MinHeight = 400
  Constraints.MinWidth = 800
  DefaultMonitor = dmMainForm
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Roboto'
  Font.Style = []
  FormStyle = fsStayOnTop
  GlassFrame.Bottom = 48
  Position = poMainFormCenter
  ScreenSnap = True
  TextHeight = 15
  object splSplitter: TSplitter
    Left = 273
    Top = 0
    Height = 409
    ExplicitLeft = 144
    ExplicitTop = 320
    ExplicitHeight = 100
  end
  object panButtons: TPanel
    Left = 0
    Top = 409
    Width = 794
    Height = 48
    Align = alBottom
    BevelOuter = bvNone
    ShowCaption = False
    TabOrder = 0
    ExplicitTop = 408
    ExplicitWidth = 790
    DesignSize = (
      794
      48)
    object Button1: TButton
      Left = 592
      Top = 8
      Width = 80
      Height = 30
      Anchors = [akTop, akRight]
      Caption = 'Save'
      ModalResult = 1
      TabOrder = 0
      ExplicitLeft = 588
    end
    object Button2: TButton
      Left = 689
      Top = 8
      Width = 80
      Height = 30
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
      ExplicitLeft = 685
    end
  end
  object crdPanels: TCardPanel
    Left = 276
    Top = 0
    Width = 518
    Height = 409
    Align = alClient
    ActiveCard = Card1
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitWidth = 514
    ExplicitHeight = 408
    object Card1: TCard
      Left = 0
      Top = 0
      Width = 518
      Height = 409
      Caption = 'Card1'
      CardIndex = 0
      TabOrder = 0
      ExplicitWidth = 514
      ExplicitHeight = 408
    end
    object Card2: TCard
      Left = 0
      Top = 0
      Width = 518
      Height = 409
      Caption = 'Card2'
      CardIndex = 1
      TabOrder = 1
    end
  end
  object ElXTree1: TElXTree
    Left = 0
    Top = 0
    Width = 273
    Height = 409
    Hint = ''
    PlusPosition = vaMiddle
    BorderColorWindow = clWindow
    Align = alLeft
    Style.FontSize = 10
    Style.FontStyles = []
    Style.FontName = 'Roboto'
    BorderStyle = bsNone
    CustomPlusMinus = True
    HeaderHeight = 19
    HeaderSections.Data = {
      F1FFFFFF010000000000000000000000FFFFFFFF000001010100000000000000
      000000001027000000000000305E42280000000001000000FFFFFFFF00000100
      0000000000000000000100000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000020000000000020000000000
      0000000000000000}
    HeaderSections.Cells = {0000000001000000010000000000}
    HorzScrollBarStyles.Width = 17
    ItemIndent = 18
    Items.Data = {
      EFFFFFFF0000000010000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF82861002
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FFFFFFFF0000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FFFFFFFF00000000000000000003000000EFFFFFFF030000
      0049004400450010000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF8286100200
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000FFFFFFFF000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000FFFFFFFF000000000100000003000000490044004500010000
      00010000000000000000000000000003000000EFFFFFFF0F0000004400650066
      00610075006C007400200046006F006C00640065007200730010000000FFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFF82861002000000000000000000000000000000
      00000000000000000000000000000000000000000000000000FFFFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000FFFFFFFF000000
      00010000000F000000440065006600610075006C007400200046006F006C0064
      0065007200730001000000010000000000000000000000000000000000EFFFFF
      FF090000005600610072006900610062006C006500730000000000FFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFF828610000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000FFFFFFFF0000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000FFFFFFFF0000000001
      000000090000005600610072006900610062006C006500730001000000010000
      000000000000000000000000000000EFFFFFFF10000000460069006C00650020
      004100730073006F00630069006100740069006F006E0000000000FFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFF828610000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000FFFFFFFF0000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000FFFFFFFF0000000001
      00000010000000460069006C00650020004100730073006F0063006900610074
      0069006F006E0001000000010000000000000000000000000000000000EFFFFF
      FF0E0000005500730065007200200049006E0074006500720066006100630065
      0010000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF8286100200000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00FFFFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00FFFFFFFF00000000010000000E0000005500730065007200200049006E0074
      0065007200660061006300650001000000010000000000000000000000000002
      000000EFFFFFFF1300000043006F0064006500200045006400690074006F0072
      0020004F007000740069006F006E00730010000000FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFF828610020000000000000000000000000000000000000000000000
      0000000000000000000000000000000000FFFFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000FFFFFFFF0000000001000000130000
      0043006F0064006500200045006400690074006F00720020004F007000740069
      006F006E00730001000000010000000000000000000000000002000000EFFFFF
      FF0600000043006F006C006F007500720000000000FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFF828610000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000FFFFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000FFFFFFFF0000000001000000060000
      0043006F006C006F007500720001000000010000000000000000000000000000
      000000EFFFFFFF0C0000004B006500790020004D0061007000700069006E0067
      00730000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF828610000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFFFFFF00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFFFFFF00000000010000000C0000004B006500790020004D00610070
      00700069006E0067007300010000000100000000000000000000000000000000
      00EFFFFFFF0D0000005400680065006D00650020004D0061006E006100670065
      00720000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF828610000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFFFFFF00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFFFFFF00000000010000000D0000005400680065006D00650020004D
      0061006E00610067006500720001000000010000000000000000000000000000
      000000EFFFFFFF080000004200750069006C00640069006E00670010000000FF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF8286100200000000000000000000000000
      000000000000000000000000000000000000000000000000000000FFFFFFFF00
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000FFFFFFFF00
      00000001000000080000004200750069006C00640069006E0067000100000001
      0000000000000000000000000004000000EFFFFFFF0C00000041004700440020
      0043006F006D00700069006C006500720000000000FFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFF828610000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000FFFFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000FFFFFFFF00000000010000000C0000
      00410047004400200043006F006D00700069006C006500720001000000010000
      000000000000000000000000000000EFFFFFFF0900000041007300730065006D
      0062006C006500720010000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF828610
      0200000000000000000000000000000000000000000000000000000000000000
      000000000000000000FFFFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000FFFFFFFF00000000010000000900000041007300730065
      006D0062006C0065007200010000000100000000000000000000000000000000
      00EFFFFFFF0800000045006D0075006C00610074006F00720010000000FFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFF82861002000000000000000000000000000000
      00000000000000000000000000000000000000000000000000FFFFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000FFFFFFFF000000
      00010000000800000045006D0075006C00610074006F00720001000000010000
      000000000000000000000000000000EFFFFFFF0600000043007500730074006F
      006D0010000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF828610020000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFFFFFF00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFFFFFF00000000010000000600000043007500730074006F006D0001
      000000010000000000000000000000000000000000}
    LineHeight = 19
    MinusPicture.Data = {
      EE000000424DEE0000000000000076000000280000000F0000000F0000000100
      04000000000078000000C40E0000C40E00001000000000000000000000004040
      4000FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000001110000000000001121100
      0000000011222110000000011221221100000011221112211000011221101122
      1100012211000112210001211000001121000111000000011100000000000000
      000000000000000000000000000000000000}
    MoveFocusOnCollapse = True
    MouseFrameSelect = False
    MouseFrameVisible = False
    MultiSelect = False
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
    ShowImages = False
    ShowLeafButton = False
    ShowLines = False
    SortSection = -1
    StoragePath = '\Tree'
    TabOrder = 2
    TabStop = True
    VertScrollBarStyles.ShowTrackHint = True
    VertScrollBarStyles.Width = 17
    FixedTopRowNum = 0
    FixedBottomRowNum = 0
    FixedColNum = 1
    GutterWidth = 0
    ExplicitHeight = 408
  end
  object ImageList1: TImageList
    Left = 556
    Top = 136
    Bitmap = {
      494C010102000800040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
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
      000000000000C0C0C000C0C0C000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0C0C00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000C0C0C000C0C0C0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C0C0C000C0C0C000C0C0C000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C0C0C000C0C0C00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000C0C0C000C0C0C00000000000C0C0C000C0C0C0000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0C0C000C0C0C000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C0C0C000C0C0C000000000000000000000000000C0C0C000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000C0C0C0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C0C0C000C0C0C0000000000000000000000000000000000000000000C0C0
      C000C0C0C0000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C0C0C000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C0C0
      C000C0C0C0000000000000000000000000000000000000000000000000000000
      0000C0C0C000C0C0C00000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000C0C0C0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0C0C000C0C0C000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C0C0C000C0C0C00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000C0C0C000C0C0C0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C0C0C000C0C0C000000000000000000000000000000000000000
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
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFF00000000FFFFFFFF00000000
      FFFFFFFF00000000FFFFF9FF00000000FF7FFCFF00000000FE3FFE7F00000000
      FC9FFF3F00000000F9CFFF9F00000000F3E7FFCF00000000E7F3FF9F00000000
      EFFBFF3F00000000FFFFFE7F00000000FFFFFCFF00000000FFFFF9FF00000000
      FFFFFFFF00000000FFFFFFFF0000000000000000000000000000000000000000
      000000000000}
  end
end