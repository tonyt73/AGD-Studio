object SelectionPanelFrame: TSelectionPanelFrame
  Left = 0
  Top = 0
  Width = 451
  Height = 87
  Margins.Left = 0
  Margins.Top = 0
  Margins.Right = 0
  Margins.Bottom = 0
  Align = alTop
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Font.Quality = fqAntialiased
  ParentFont = False
  TabOrder = 0
  object panProjectInfo: TPanel
    Left = 0
    Top = 0
    Width = 431
    Height = 87
    Align = alClient
    BevelOuter = bvNone
    Padding.Left = 16
    Padding.Top = 4
    Padding.Right = 8
    Padding.Bottom = 8
    TabOrder = 0
    StyleElements = [seFont, seBorder]
    OnClick = lblProjectNameClick
    OnMouseMove = panProjectInfoMouseMove
    DesignSize = (
      431
      87)
    object lblProjectPath: TLabel
      Left = 19
      Top = 45
      Width = 280
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = 'Documents\Retro Studio\Big Sprite Demo'
      EllipsisPosition = epPathEllipsis
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Roboto'
      Font.Style = []
      Font.Quality = fqAntialiased
      ParentFont = False
      OnClick = lblProjectNameClick
      OnMouseMove = panProjectInfoMouseMove
      ExplicitWidth = 311
    end
    object lblProjectName: TLabel
      AlignWithMargins = True
      Left = 19
      Top = 4
      Width = 280
      Height = 26
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = 'Big Sprite Demo 2'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'Roboto'
      Font.Style = [fsBold]
      Font.Quality = fqAntialiased
      ParentFont = False
      OnClick = lblProjectNameClick
      OnMouseMove = panProjectInfoMouseMove
    end
    object lblMachine: TLabel
      Left = 19
      Top = 29
      Width = 280
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = 'Documents\Retro Studio\Big Sprite Demo'
      EllipsisPosition = epPathEllipsis
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Roboto'
      Font.Style = [fsBold]
      Font.Quality = fqAntialiased
      ParentFont = False
      OnClick = lblProjectNameClick
      OnMouseMove = panProjectInfoMouseMove
      ExplicitWidth = 311
    end
    object imgLogo: TImage
      Left = 305
      Top = 6
      Width = 120
      Height = 56
      Anchors = [akTop, akRight, akBottom]
      Transparent = True
      Visible = False
      OnClick = lblProjectNameClick
      OnMouseMove = panProjectInfoMouseMove
      ExplicitLeft = 336
    end
    object prgLoading: TProgressBar
      Left = 19
      Top = 68
      Width = 406
      Height = 14
      Anchors = [akLeft, akTop, akRight]
      Position = 100
      Style = pbstMarquee
      BarColor = clRed
      TabOrder = 0
      Visible = False
      StyleElements = []
    end
  end
  object panRemove: TPanel
    Left = 431
    Top = 0
    Width = 20
    Height = 87
    Align = alRight
    BevelOuter = bvNone
    Padding.Right = 4
    TabOrder = 1
    StyleElements = [seFont, seBorder]
    OnClick = lblProjectNameClick
    OnMouseMove = panProjectInfoMouseMove
    object imgRemove: TImage
      Left = 0
      Top = 6
      Width = 16
      Height = 16
      Hint = 'Remove the item from the list'
      AutoSize = True
      ParentShowHint = False
      Picture.Data = {
        0954506E67496D61676589504E470D0A1A0A0000000D49484452000000100000
        001008060000001FF3FF610000001974455874536F6674776172650041646F62
        6520496D616765526561647971C9653C000001604944415478DA63FCFFFF3F03
        23232303081C7130F80FA26D0E5C8008A0017479B05E98012049A3E62EB0C273
        B56518866093871B70D4D1F0BF617503C387BE5AB00281A26686F3AD0D704340
        9AB1C95BEF3FCF8830A0B89CE1D3AC6EB88D7C69A50CE77B3BC16C5C72700380
        5E3006DA72C6203B8FE1DBB29970855C51E9601A5DECC2D44920D79900F59E65
        440A44B02186C9E90CDF372DC516860C9C7ED10CE7E7CE046B0672CFA2042214
        400C898D67F8B967138A6676173F86F38B17C23563C4024A68874530FC3ABE0F
        C500364B278673AB56A0C40E860160CD81410C7F2F9CC4EA056603738673EBD7
        E14E07C63EDE0CFF6E5E816B6052D701D3E86267B76CC54C0726EE6E0CFF1FDD
        832B6494536238B37317988D4B0E251D98393932FC7FF302A2404482E1D4BEFD
        B00003B9EE0C36798C74606167035670E2D01194D086C50EBA3CD67400CD2CC8
        9A51A218591E6B3A80D2E89AB1CAC30DA004000057550FF07637089B00000000
        49454E44AE426082}
      ShowHint = True
      OnClick = imgRemoveClick
    end
  end
end
