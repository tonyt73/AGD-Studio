object SelectionPanelFrame: TSelectionPanelFrame
  Left = 0
  Top = 0
  Width = 439
  Height = 85
  Margins.Left = 0
  Margins.Top = 0
  Margins.Right = 0
  Margins.Bottom = 0
  Align = alTop
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Roboto'
  Font.Style = []
  Font.Quality = fqAntialiased
  ParentFont = False
  TabOrder = 0
  object panProjectInfo: TPanel
    Left = 0
    Top = 0
    Width = 419
    Height = 85
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
      419
      85)
    object lblProjectPath: TLabel
      Left = 19
      Top = 45
      Width = 268
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = 'Documents\AGD Studio\Demo'
      EllipsisPosition = epPathEllipsis
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Roboto'
      Font.Style = []
      Font.Quality = fqAntialiased
      ParentFont = False
      OnClick = lblProjectNameClick
      OnMouseMove = panProjectInfoMouseMove
      ExplicitWidth = 280
    end
    object lblProjectName: TLabel
      AlignWithMargins = True
      Left = 19
      Top = 4
      Width = 268
      Height = 26
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = 'Big Sprite Demo 2'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 20
      Font.Name = 'Roboto'
      Font.Style = [fsBold]
      Font.Quality = fqAntialiased
      ParentFont = False
      OnClick = lblProjectNameClick
      OnMouseMove = panProjectInfoMouseMove
      ExplicitWidth = 280
    end
    object lblMachine: TLabel
      Left = 19
      Top = 29
      Width = 268
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = 'Documents\AGD Studio\Demo'
      EllipsisPosition = epPathEllipsis
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Roboto'
      Font.Style = [fsBold]
      Font.Quality = fqAntialiased
      ParentFont = False
      OnClick = lblProjectNameClick
      OnMouseMove = panProjectInfoMouseMove
      ExplicitWidth = 280
    end
    object imgLogo: TImage
      Left = 293
      Top = 6
      Width = 120
      Height = 54
      Anchors = [akTop, akRight, akBottom]
      Transparent = True
      Visible = False
      OnClick = lblProjectNameClick
      OnMouseMove = panProjectInfoMouseMove
      ExplicitLeft = 305
      ExplicitHeight = 56
    end
    object prgLoading: TProgressBar
      Left = 19
      Top = 68
      Width = 394
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
    Left = 419
    Top = 0
    Width = 20
    Height = 85
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
    object imgOpenProjectFolder: TImage
      Left = 0
      Top = 28
      Width = 16
      Height = 16
      Hint = 'Open the project folder in Explorer'
      AutoSize = True
      ParentShowHint = False
      Picture.Data = {
        0954506E67496D61676589504E470D0A1A0A0000000D49484452000000100000
        001008060000001FF3FF610000001974455874536F6674776172650041646F62
        6520496D616765526561647971C9653C000002CA4944415478DA8D525D485371
        14FFFDEFBD9BE2C4C4A5681961D1870FBA9161511AD64A7D53088242D4969941
        168645D84B9150E04050F30B69622FF990859594919A19214A39A3C0056E0DB3
        206B7D20E87677FF9D7BAF9B3E76B673FFE71CCEF99D4F36DD6EF32B72209E2B
        21A8C404114C94BE3026149016A59A1026A6FD2530361E36B3A9965C6EA97202
        4159771245BC6D39A18290DF6A6C0483120892E13B13A4244D7FD7B49F5B4F77
        22E06E00E70C868D472198B601028B64D53F5C7F24035CADA5100DD1D9946142
        07A86844C0E354D3939F1271562B6004C434590552206CAD21003BDCDF02D6F4
        CDF12E02C8E1D693F590E71F9297B8DA323D8228C0333103BFEFEB4A415C6326
        496A1BC4C60704904B0057C117862948D252E95533CC8E7F40EC3A09497937F5
        12B8CAEAB0695E04E26AB3D30C9A0F70EBA95A78069C58989D5BD3B680B4ACED
        306F4AD4E48C1E076C5B807824E39AED12649E8637F71CE36CEA761EDF59580C
        EFABC7D851D2416D86F456C468608E7418483620BBEB0ABACA6AD13DE680D9B8
        07173614E3497F5F0D73B51EE2299916C84B41A4641781FF784E9D44E3C66837
        EEBB7DEA5841A300A3D93A2BAE6361F123FAA77BC1BC09705CFE6966AE361B8F
        4D342339732F62CCEB81651F608C81B5E922FACEB76031F854DB0EA7ED18857C
        8C7CAA46466A2906A67B3036835E36DD71982BC1202C67CE014BBFA88565AA3A
        06BB1BECE8ACACC6E4E7E6C811295C9FA54015ED4AB5A3EEEE1DBAC4F623BF05
        28718A1CA213A03DD3CF2444A1E4CF33DCB21F84D73FAC05ABE7110A468E15BE
        7960F43586D4815BEA8EA75B837228A46E9971AA5666F258E64C799C0985A493
        8116479B2B3BA6CB5E5AD6CB110C0ED7E32C7BDF998F8CCA41D3CA9584499593
        8913C286825B982C2B01DC6E0A1ED282AB8A1AE1D100D692405710CB8C28FFFB
        885E558F54C0F7E5002F063044C1156A70E466FE93B2565E3FF16CD8F80F895F
        06A55D5D58870000000049454E44AE426082}
      ShowHint = True
      OnClick = imgOpenProjectFolderClick
    end
  end
end
