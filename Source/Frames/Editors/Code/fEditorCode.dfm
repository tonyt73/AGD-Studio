inherited frmEditorCode: TfrmEditorCode
  Width = 978
  Height = 611
  Font.Height = -11
  Font.Name = 'Roboto'
  ParentFont = False
  ExplicitWidth = 978
  ExplicitHeight = 611
  object evEditor: TLMDEditView
    Left = 0
    Top = 40
    Width = 978
    Height = 552
    Align = alClient
    BevelEdges = []
    BevelInner = bvNone
    BevelOuter = bvNone
    TabOrder = 0
    Document = lmdDocument
    ViewSettings = [vsShowWrapRuler, vsHideShowScrollbars, vsHighlightSelectedLine, vsAutoIndent, vsRightClickMovesCursor, vsBackspaceUnindents, vsDragDropEditing]
    TabWidth = 4
    WrapRulerWidth = 64
    Color = clBlack
    SelectedLineBg = 2105376
    DebugFrameLineBg = clMedGray
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    Gutter.BookmarksBarBg = clGrayText
    Gutter.LinesBarBg = clMaroon
    Gutter.FoldsBarBg = clGray
    CustomKeyBindings = <>
    CompletionSettings.ItemHeight = 13
    OnStatusChanged = evEditorStatusChanged
    OnKeyUp = evEditorKeyUp
    OnEnter = evEditorEnter
    GutterBarsEmpty = False
  end
  object sbStatus: TStatusBar
    Left = 0
    Top = 592
    Width = 978
    Height = 19
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Roboto'
    Font.Style = []
    Panels = <
      item
        Width = 50
      end
      item
        Width = 50
      end
      item
        Width = 50
      end
      item
        Width = 50
      end
      item
        Width = 50
      end
      item
        Width = 50
      end
      item
        Width = 50
      end
      item
        Width = 50
      end>
    UseSystemFont = False
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 978
    Height = 40
    AutoSize = True
    ButtonHeight = 40
    ButtonWidth = 40
    Caption = 'ToolBar1'
    Images = vilToolbar
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    object tbrFormatCode: TToolButton
      Left = 0
      Top = 0
      Action = actGoToLine
    end
    object ToolButton1: TToolButton
      Left = 40
      Top = 0
      Width = 8
      Caption = 'ToolButton1'
      ImageIndex = 25
      ImageName = 'document_next'
      Style = tbsSeparator
    end
    object btnChangeFont: TToolButton
      Left = 48
      Top = 0
      Action = actFont
      ParentShowHint = False
      ShowHint = True
    end
    object ToolButton5: TToolButton
      Left = 88
      Top = 0
      Width = 8
      Caption = 'ToolButton5'
      ImageIndex = 30
      Style = tbsSeparator
    end
  end
  object lmdDocument: TLMDEditDocument
    Lines.Strings = (
      '')
    UndoLimit = 8192
    WordSeparators = '[]();.,'#39'"-:+/\'
    SyntaxSchemes = <
      item
        Name = 'AGD'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '  <Scheme name='#39'Text'#39' inherit='#39'Numbers'#39'>'
          '        <Regex token0='#39'email'#39'>'
          '            [_a-zA-Z\d\-\.]{1,40}'
          '            @ '
          '            ([_ a-z A-Z \d \-]+ '
          '            (\. [_ a-z A-Z \d \-]+ )+ )'
          '        </Regex>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'Numbers'#39'>'
          
            '    <Regex token0='#39'number'#39'>\b (0x \d+ [lL]? | \d+ (e \d*)? [lLdD' +
            'fF]? ) \b</Regex>'
          
            '    <Regex token0='#39'number'#39'>\b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? ' +
            '\d+) \b</Regex>'
          '  </Scheme>'
          ''
          
            '  <Scheme name='#39'Comment'#39' inherit='#39'Text'#39' defaultToken='#39'comment'#39'  ' +
            '/>'
          ''
          '  <Scheme name='#39'String'#39' inherit='#39'Text'#39' defaultToken='#39'string'#39'>'
          '  </Scheme>'
          ''
          
            '  <Scheme name='#39'BadString'#39' inherit='#39'String'#39' defaultToken='#39'badStr' +
            'ing'#39'>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'StringFind'#39'>'
          '    <Regex innerScheme='#39'BadString'#39' > '
          '        &quot; (.*?\\ &quot; )*? .* $ '
          '    </Regex>'
          ''
          '    <Regex innerScheme='#39'String'#39' priority='#39'10'#39'> '
          '        &quot; (.*?\\ &quot; )*? &quot; c?'
          '    </Regex>'
          ''
          '    <Regex innerScheme='#39'String'#39' priority='#39'20'#39'> '
          '        &quot; (.*?\\ &quot; )*? .*? [^\\] &quot; c?'
          '    </Regex>  '
          ''
          '    <Regex innerScheme='#39'String'#39' priority='#39'30'#39'> '
          '        &quot;  &quot; c?'
          '    </Regex>    '
          '  </Scheme>'
          ''
          ''
          ''
          '  <Scheme name='#39'Main'#39' inherit='#39'Numbers'#39' inherit0='#39'StringFind'#39
          '          defaultToken='#39'default'#39
          '          allIgnoreCase='#39'true'#39'>'
          
            '    <KeywordRegex moreWordChars='#39'.'#39'>\b[a-zA-Z_][\w_]*\b</Keyword' +
            'Regex>'
          ''
          '    <Keywords>'
          '        ADD'
          '        ADDBONUS'
          '        ANIMATE'
          '        ANIMBACK'
          '        AT'
          '        BEEP'
          '        BONUS'
          '        BORDER'
          '        CLS'
          '        CLUT'
          '        CLW'
          '        COLOUR'
          '        CRASH'
          '        DECAYPARTICLE'
          '        DEFINEKEY'
          '        DEFINEPARTICLE'
          '        DELAY'
          '        DETECTOBJECT'
          '        DISPLAY'
          '        DIVIDE'
          '        DIG'
          '        ELSE'
          '        ENDGAME'
          '        ENDREPEAT'
          '        ENDSPRITE'
          '        ENDIF'
          '        ENDWHILE'
          '        EXIT'
          '        EXPLODE'
          '        FALL'
          '        GET'
          '        GETBLOCK'
          '        GETRANDOM'
          '        IF'
          '        INK'
          '        JUMP'
          '        KILL'
          '        LASER'
          '        LET'
          '        MENU'
          '        MESSAGE'
          '        MULTIPLY'
          '        NEXTLEVEL'
          '        NEWPARTICLE'
          '        OTHER'
          '        PALETTE'
          '        PAPER'
          '        PARTICLEDOWN'
          '        PARTICLELEFT'
          '        PARTICLERIGHT'
          '        PARTICLEUP'
          '        PLOT'
          '        PRINT'
          '        PRINTMODE'
          '        PUT'
          '        PUTBLOCK'
          '        RANOMIZE'
          '        READ'
          '        REDRAW'
          '        REMOVE'
          '        REMOVEOBJ'
          '        REPEAT'
          '        RESTART'
          '        RESTORE'
          '        SCORE'
          '        SCREENDOWN'
          '        SCREENLEFT'
          '        SCREENRIGHT'
          '        SCREENUP'
          '        SHOWBONUS'
          '        SHOWSCORE'
          '        SHOWHIGH'
          '        SILENCE'
          '        SOUND'
          '        SPAWN'
          '        SPAWNED'
          '        SPRITEDOWN'
          '        SPRITEINK'
          '        SPRITELEFT'
          '        SPRITERIGHT'
          '        SPRITEUP'
          '        STAR'
          '        SUBTRACT'
          '        TRAIL'
          '        UNDOSPRITEMOVE'
          '        WAITKEY'
          '        WHILE'
          '        ZEROBONUS'
          '            '
          '    </Keywords>'
          ''
          '    <!--Regex innerScheme='#39'Comment'#39' regex='#39'Rem.*$'#39' /-->'
          '    <Regex innerScheme='#39'Comment'#39' regex=" ;.*$ " />'
          ''
          
            '    <Regex token0='#39'symbol'#39' regex='#39'[    \]    \[  \( \) &gt; &lt;' +
            '  &amp; ]'#39' />'
          '    <Regex token0='#39'symbol'#39' regex='#39'[-=+^;,]'#39' />'
          ''
          '    <SkipSyntaxToken token='#39'comment'#39' />'
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start> '
          '            [ kw:IF ]  '
          '        </Start>      '
          '        <End> kw:ENDIF</End>'
          '    </SyntaxBlock>'
          '        '
          '    <SyntaxBlock capture="true">'
          '        <Start>   [ kw:WHILE ]    </Start>'
          ''
          '        <End> kw:ENDWHILE</End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start>   [ kw:REPEAT ]    </Start>'
          ''
          '        <End> kw:ENDREPEAT  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start>   [ kw:SPAWNED ]    </Start>'
          ''
          '        <End> kw:ENDSPRITE  </End>'
          '    </SyntaxBlock>'
          '  </Scheme>'
          '</SchemeList>')
      end>
    ColorSchemes = <
      item
        Name = 'default'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          '<Attributes>'
          #9'<Token name="default" textColor="#0"/>'
          #9'<Token name="defaultEmbed" backgroundColor="#ECE9D8"/>'
          #9'<Token name="docStart" fontStyle="bold"/>'
          #9'<Token name="docEnd" fontStyle="bold"/>'
          #9'<Token name="docBlockStart" fontStyle="bold"/>'
          #9'<Token name="docBlockEnd" fontStyle="bold"/>'
          #9'<Token name="docInstruction" fontStyle="bold"/>'
          #9'<Token name="docDefault" backgroundColor="#ECE9D8"/>'
          #9'<Token name="comment" textColor="#008000"/>'
          #9'<Token name="commentStart" textColor="#008000"/>'
          #9'<Token name="commentEnd" textColor="#008000"/>'
          #9'<Token name="keyword" fontStyle="bold"/>'
          #9'<Token name="privateSymbol" textColor="Navy"/>'
          #9'<Token name="email" fontStyle="bold"/>'
          
            #9'<Token name="hairy" textColor="#000080" fontStyle="bold, italic' +
            ', underline, strikeOut"/>'
          #9'<Token name="number" textColor="Blue"/>'
          #9'<Token name="symbol" textColor="Blue"/>'
          #9'<Token name="string" textColor="Blue"/>'
          #9'<Token name="blockStart" fontStyle="bold"/>'
          #9'<Token name="blockEnd" fontStyle="bold"/>'
          #9'<Token name="badString" textColor="Red"/>'
          #9'<Token name="preprocessor" textColor="#008080"/>'
          #9'<Token name="badPreprocessor" textColor="red"/>'
          #9'<Token name="escaped" textColor="Navy"/>'
          
            #9'<Token name="quotedVariable" textColor="Navy" fontStyle="bold"/' +
            '>'
          #9'<Token name="regexStart" textColor="Navy" fontStyle="bold"/>'
          
            #9'<Token name="regexEnd" textColor="Navy" fontStyle="bold"/><!--h' +
            'tml/xml tokens-->'
          #9'<Token name="tagOpen" textColor="Purple"/>'
          #9'<Token name="tagClose" textColor="Purple"/>'
          
            #9'<Token name="dtdTagStartEnd" textColor="Purple" fontStyle="bold' +
            '"/>'
          #9'<Token name="url" textColor="Red"/>'
          #9'<Token name="fpi" textColor="Red" fontStyle="bold"/>'
          #9'<Token name="entity" textColor="#FF4500"/>'
          
            #9'<Token name="attributeName" backgroundColor="Black" textColor="' +
            '#583485"/>'
          #9'<Token name="attributeValue" textColor="Blue"/>'
          #9'<Token name="badAttributeValue" textColor="Red"/>'
          #9'<Token name="cssRule" textColor="#583485" fontStyle="bold"/>'
          #9'<Token name="cssRelSymbol" fontStyle="bold"/>'
          #9'<Token name="cssUrlHref" fontStyle="underline"/>'
          #9'<Token name="cssUrlAttr"/>'
          #9'<Token name="cssAttrListBG" textColor="Blue"/>'
          
            #9'<Token name="cdataTagStart" textColor="Purple" fontStyle="bold"' +
            '/>'
          #9'<Token name="cdataTagEnd" textColor="Purple" fontStyle="bold"/>'
          
            #9'<Token name="xmlDeclStart" textColor="Purple" fontStyle="bold"/' +
            '>'
          #9'<Token name="xmlDeclEnd" textColor="Purple" fontStyle="bold"/>'
          '</Attributes>')
      end
      item
        Name = 'Dark'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          '<Attributes>'
          
            #9'<Token name="default" backgroundColor="Black" textColor="White"' +
            '/>'
          #9'<Token name="defaultEmbed" backgroundColor="#ECE9D8"/>'
          
            #9'<Token name="docStart" backgroundColor="Black" fontStyle="bold"' +
            '/>'
          #9'<Token name="docEnd" backgroundColor="Black" fontStyle="bold"/>'
          
            #9'<Token name="docBlockStart" backgroundColor="Black" fontStyle="' +
            'bold"/>'
          
            #9'<Token name="docBlockEnd" backgroundColor="Black" fontStyle="bo' +
            'ld"/>'
          
            #9'<Token name="docInstruction" backgroundColor="Black" fontStyle=' +
            '"bold"/>'
          #9'<Token name="docDefault" backgroundColor="Black"/>'
          
            #9'<Token name="comment" backgroundColor="Black" textColor="Green"' +
            '/>'
          
            #9'<Token name="commentStart" backgroundColor="Black" textColor="G' +
            'reen"/>'
          
            #9'<Token name="commentEnd" backgroundColor="Black" textColor="Gre' +
            'en"/>'
          
            #9'<Token name="keyword" backgroundColor="Black" textColor="Aqua" ' +
            'fontStyle="bold"/>'
          
            #9'<Token name="privateSymbol" backgroundColor="Black" textColor="' +
            'Fuchsia"/>'
          
            #9'<Token name="email" backgroundColor="Black" textColor="Olive" f' +
            'ontStyle="bold"/>'
          
            #9'<Token name="hairy" backgroundColor="Black" textColor="Navy" fo' +
            'ntStyle="italic bold underline strikeOut"/>'
          
            #9'<Token name="number" backgroundColor="Black" textColor="Yellow"' +
            '/>'
          
            #9'<Token name="symbol" backgroundColor="Black" textColor="Yellow"' +
            '/>'
          #9'<Token name="string" backgroundColor="Black" textColor="Blue"/>'
          
            #9'<Token name="blockStart" backgroundColor="Black" fontStyle="bol' +
            'd"/>'
          
            #9'<Token name="blockEnd" backgroundColor="Black" fontStyle="bold"' +
            '/>'
          
            #9'<Token name="badString" backgroundColor="Black" textColor="Red"' +
            '/>'
          
            #9'<Token name="preprocessor" backgroundColor="Black" textColor="T' +
            'eal"/>'
          
            #9'<Token name="badPreprocessor" backgroundColor="Maroon" textColo' +
            'r="Red"/>'
          
            #9'<Token name="escaped" backgroundColor="Black" textColor="Navy"/' +
            '>'
          
            #9'<Token name="quotedVariable" backgroundColor="Black" textColor=' +
            '"Navy" fontStyle="bold"/>'
          
            #9'<Token name="regexStart" backgroundColor="Black" textColor="Nav' +
            'y" fontStyle="bold"/>'
          
            #9'<Token name="regexEnd" backgroundColor="Black" textColor="Navy"' +
            ' fontStyle="bold"/><!--html/xml tokens-->'
          
            #9'<Token name="tagOpen" backgroundColor="Black" textColor="Purple' +
            '"/>'
          
            #9'<Token name="tagClose" backgroundColor="Maroon" textColor="Purp' +
            'le"/>'
          
            #9'<Token name="dtdTagStartEnd" backgroundColor="Black" textColor=' +
            '"Purple" fontStyle="bold"/>'
          #9'<Token name="url" backgroundColor="Black" textColor="Red"/>'
          
            #9'<Token name="fpi" backgroundColor="Black" textColor="Red" fontS' +
            'tyle="bold"/>'
          
            #9'<Token name="entity" backgroundColor="Black" textColor="#FF4500' +
            '"/>'
          
            #9'<Token name="attributeName" backgroundColor="Black" textColor="' +
            '#583485"/>'
          
            #9'<Token name="attributeValue" backgroundColor="Black" textColor=' +
            '"Blue"/>'
          
            #9'<Token name="badAttributeValue" backgroundColor="Black" textCol' +
            'or="Red"/>'
          
            #9'<Token name="cssRule" backgroundColor="Black" textColor="#58348' +
            '5" fontStyle="bold"/>'
          
            #9'<Token name="cssRelSymbol" backgroundColor="Black" fontStyle="b' +
            'old"/>'
          
            #9'<Token name="cssUrlHref" backgroundColor="Black" fontStyle="und' +
            'erline"/>'
          #9'<Token name="cssUrlAttr" backgroundColor="Black"/>'
          
            #9'<Token name="cssAttrListBG" backgroundColor="Black" textColor="' +
            'Blue"/>'
          
            #9'<Token name="cdataTagStart" backgroundColor="Black" textColor="' +
            'Purple" fontStyle="bold"/>'
          
            #9'<Token name="cdataTagEnd" backgroundColor="Black" textColor="Pu' +
            'rple" fontStyle="bold"/>'
          
            #9'<Token name="xmlDeclStart" backgroundColor="Black" textColor="P' +
            'urple" fontStyle="bold"/>'
          
            #9'<Token name="xmlDeclEnd" backgroundColor="Black" textColor="Pur' +
            'ple" fontStyle="bold"/>'
          '</Attributes>')
      end>
    ActiveSyntaxScheme = 'AGD'
    ActiveColorScheme = 'Dark'
    Left = 64
    Top = 48
  end
  object Actions: TActionList
    Images = vilToolbar
    Left = 360
    Top = 128
    object actBmkSet_0: TAction
      Category = 'Bookmarks'
      Caption = 'actBmkSet_0'
      ShortCut = 24624
    end
    object actBmkSet_9: TAction
      Tag = 9
      Category = 'Bookmarks'
      Caption = 'actBmkSet_9'
      ShortCut = 24633
    end
    object actBmkSet_8: TAction
      Tag = 8
      Category = 'Bookmarks'
      Caption = 'actBmkSet_8'
      ShortCut = 24632
    end
    object actBmkSet_7: TAction
      Tag = 7
      Category = 'Bookmarks'
      Caption = 'actBmkSet_7'
      ShortCut = 24631
    end
    object actBmkSet_6: TAction
      Tag = 6
      Category = 'Bookmarks'
      Caption = 'actBmkSet_6'
      ShortCut = 24630
    end
    object actBmkSet_5: TAction
      Tag = 5
      Category = 'Bookmarks'
      Caption = 'actBmkSet_5'
      ShortCut = 24629
    end
    object actUndo: TEditUndo
      Category = 'Edit'
      Caption = '&Undo'
      Hint = 'Undo|Reverts the last action'
      ImageIndex = 3
      ImageName = 'arrow_undo'
      OnExecute = actUndoExecute
      OnUpdate = actUndoUpdate
    end
    object actRedo: TEditUndo
      Category = 'Edit'
      Caption = '&Redo'
      Hint = 'Redo'
      ImageIndex = 4
      ImageName = 'arrow_redo'
      OnExecute = actRedoExecute
    end
    object actBmkSet_4: TAction
      Tag = 4
      Category = 'Bookmarks'
      Caption = 'actBmkSet_4'
      ShortCut = 24628
    end
    object actBmkSet: TAction
      Category = 'Bookmarks'
      Caption = 'Set bookmark'
      ImageIndex = 23
      ImageName = 'bookmark'
    end
    object actBmkDeleteLast: TAction
      Category = 'Bookmarks'
      Caption = 'Delete bookmark'
      ImageIndex = 10
      ImageName = 'text_replace'
    end
    object actBmkDeleteAll: TAction
      Category = 'Bookmarks'
      Caption = 'Clear bookmarks'
      ImageIndex = 2
      ImageName = 'disk'
    end
    object actGoToLine: TAction
      Category = 'Edit'
      Caption = 'Go to line'
      Hint = 'Goto line number'
      ImageIndex = 24
      ImageName = 'document_insert'
      ShortCut = 16455
      OnExecute = actGoToLineExecute
    end
    object actFoldTops: TAction
      Category = 'Fold'
      Caption = 'Fold all top folds'
    end
    object actUnfoldTops: TAction
      Category = 'Fold'
      Caption = 'Unfold all top folds'
    end
    object actFoldAll: TAction
      Category = 'Fold'
      Caption = 'Fold all'
    end
    object actUnfoldAll: TAction
      Category = 'Fold'
      Caption = 'Unfold all'
    end
    object actFoldCurrentTop: TAction
      Category = 'Fold'
      Caption = 'actFoldCurrentTop'
    end
    object actFoldAllInCurrent: TAction
      Category = 'Fold'
      Caption = 'Fold all here'
    end
    object actFoldTopsInCurrent: TAction
      Category = 'Fold'
      Caption = 'Fold tops here'
    end
    object actUnfoldTopsInCurrent: TAction
      Category = 'Fold'
      Caption = 'Unfold tops here'
    end
    object actUnfoldAllInCurrent: TAction
      Category = 'Fold'
      Caption = 'Unfold all here'
    end
    object actSearch: TAction
      Category = 'Edit'
      Caption = 'Search'
      ImageIndex = 9
      ImageName = 'find'
      OnExecute = actSearchExecute
    end
    object actReplace: TAction
      Category = 'Edit'
      Caption = 'actReplace'
      ImageIndex = 10
      ImageName = 'text_replace'
      ShortCut = 16456
      OnExecute = actReplaceExecute
    end
    object actSaveFile: TAction
      Category = 'File'
      Caption = 'Save'
      ImageIndex = 2
      ImageName = 'disk'
      ShortCut = 16467
      OnExecute = actSaveFileExecute
    end
    object actBmkSet_1: TAction
      Tag = 1
      Category = 'Bookmarks'
      Caption = 'actBmkSet_1'
      ShortCut = 24625
    end
    object actBmkSet_2: TAction
      Tag = 2
      Category = 'Bookmarks'
      Caption = 'actBmkSet_2'
      ShortCut = 24626
    end
    object actBmkSet_3: TAction
      Tag = 3
      Category = 'Bookmarks'
      Caption = 'actBmkSet_3'
      ShortCut = 24627
    end
    object actBmkGoto_1: TAction
      Tag = 1
      Category = 'Bookmarks'
      Caption = 'actBmkGoto_1'
      ShortCut = 16433
    end
    object actBmkGoto_2: TAction
      Tag = 2
      Category = 'Bookmarks'
      Caption = 'actBmkGoto_2'
      ShortCut = 16434
    end
    object actBmkGoto_3: TAction
      Tag = 3
      Category = 'Bookmarks'
      Caption = 'actBmkGoto_3'
      ShortCut = 16435
    end
    object actBmkGoto_4: TAction
      Tag = 4
      Category = 'Bookmarks'
      Caption = 'actBmkGoto_4'
      ShortCut = 16436
    end
    object actBmkGoto_5: TAction
      Tag = 5
      Category = 'Bookmarks'
      Caption = 'actBmkGoto_5'
      ShortCut = 16437
    end
    object actBmkGoto_6: TAction
      Tag = 6
      Category = 'Bookmarks'
      Caption = 'actBmkGoto_6'
      ShortCut = 16438
    end
    object actBmkGoto_7: TAction
      Tag = 7
      Category = 'Bookmarks'
      Caption = 'actBmkGoto_7'
      ShortCut = 16439
    end
    object actBmkGoto_8: TAction
      Tag = 8
      Category = 'Bookmarks'
      Caption = 'actBmkGoto_8'
      ShortCut = 16440
    end
    object actBmkGoto_9: TAction
      Tag = 9
      Category = 'Bookmarks'
      Caption = 'actBmkGoto_9'
      ShortCut = 16441
    end
    object actBmkGoto_0: TAction
      Category = 'Bookmarks'
      Caption = 'actBmkGoto_0'
      ShortCut = 16432
    end
    object actCopy: TAction
      Category = 'Edit'
      Caption = 'Copy'
      ImageIndex = 5
      ImageName = 'page_white_copy'
      ShortCut = 16451
      OnExecute = actCopyExecute
    end
    object actPaste: TAction
      Category = 'Edit'
      Caption = 'Paste'
      ImageIndex = 7
      ImageName = 'paste_plain'
      ShortCut = 16470
      OnExecute = actPasteExecute
    end
    object actCut: TAction
      Category = 'Edit'
      Caption = 'Cut'
      ImageIndex = 6
      ImageName = 'cut'
      ShortCut = 16472
      OnExecute = actCutExecute
    end
    object actRefreshSchemes: TAction
      Caption = 'Refr schemes'
      ShortCut = 49234
    end
    object actSearchNext: TAction
      Category = 'Edit'
      Caption = 'Search/replace next'
      ImageIndex = 9
      ImageName = 'find'
      ShortCut = 114
      OnExecute = actSearchNextExecute
    end
    object actToggleLineWrap: TAction
      Category = 'Settings'
      AutoCheck = True
      Caption = 'Toggle Line Wrap'
      Checked = True
      Hint = 'Toggle Line Wrap'
      ImageIndex = 28
      ImageName = 'vrule'
      ShortCut = 16471
    end
    object actFont: TAction
      Category = 'Settings'
      Hint = 'Change editor font'
      ImageIndex = 29
      ImageName = 'font'
      OnExecute = actFontExecute
    end
    object actSearchPrevious: TAction
      Category = 'Edit'
      Caption = 'Search/replace previous'
      ShortCut = 8306
      OnExecute = actSearchPreviousExecute
    end
    object actVariableEditor: TAction
      Category = 'Toolbar'
      Caption = 'Variable Editor'
      Hint = 'Toggle Variable Editor'
      ShortCut = 24662
    end
    object actFormat: TAction
      Category = 'Edit'
      Caption = 'actFormatCode'
      Hint = 'Format Code'
      ImageIndex = 20
      ImageName = 'source_code'
      ShortCut = 123
      OnExecute = actFormatExecute
    end
    object actZoomIn: TAction
      Category = 'Edit'
      Caption = 'Zoom In'
      Hint = 'Zoom into document'
      ImageIndex = 11
      ImageName = 'zoom_in'
      OnExecute = actZoomInExecute
    end
    object actZoomOut: TAction
      Category = 'Edit'
      Caption = 'Zoo mOut'
      Hint = 'Zoom out of document'
      ImageIndex = 12
      ImageName = 'zoom_out'
      OnExecute = actZoomOutExecute
    end
    object actZoomReset: TAction
      Category = 'Edit'
      Caption = 'Zoom Reset'
      Hint = 'Reset document zoom'
      ImageIndex = 13
      ImageName = 'zoom_actual'
      OnExecute = actZoomResetExecute
    end
  end
  object FontDialog: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Roboto'
    Font.Style = []
    Options = [fdFixedPitchOnly, fdApplyButton]
    OnApply = FontDialogApply
    Left = 176
    Top = 50
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
        CollectionName = 'arrow_right'
        Name = 'arrow_right'
      end
      item
        CollectionIndex = 18
        CollectionName = 'arrow_left'
        Name = 'arrow_left'
      end
      item
        CollectionIndex = 19
        CollectionName = 'magic_wand_2'
        Name = 'magic_wand_2'
      end
      item
        CollectionIndex = 20
        CollectionName = 'source_code'
        Name = 'source_code'
      end
      item
        CollectionIndex = 21
        CollectionName = 'book_next'
        Name = 'book_next'
      end
      item
        CollectionIndex = 22
        CollectionName = 'book_previous'
        Name = 'book_previous'
      end
      item
        CollectionIndex = 23
        CollectionName = 'bookmark'
        Name = 'bookmark'
      end
      item
        CollectionIndex = 24
        CollectionName = 'document_insert'
        Name = 'document_insert'
      end
      item
        CollectionIndex = 25
        CollectionName = 'document_next'
        Name = 'document_next'
      end
      item
        CollectionIndex = 26
        CollectionName = 'document_back'
        Name = 'document_back'
      end
      item
        CollectionIndex = 27
        CollectionName = 'text_document_wrap'
        Name = 'text_document_wrap'
      end
      item
        CollectionIndex = 28
        CollectionName = 'vrule'
        Name = 'vrule'
      end
      item
        CollectionIndex = 29
        CollectionName = 'font'
        Name = 'font'
      end>
    ImageCollection = icToolbar
    Width = 24
    Height = 24
    Left = 360
    Top = 248
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
        Name = 'arrow_right'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000001E34944415478DAEC973B48C3501486FFB4A9582BD43A38
              39288893824E0A220EBE40DA21431D7450045741DDC4D1828AB8B98A0E76D0C1
              41A158ACDA6215670B82E0932A888A2296D2E6E5B96D8A55D7A471C80927DC9B
              3B9CEFFCF96F2EE1545585996183C9610158001680E9004647996F19EAC02276
              68CC9BA1804B5680CE7A787B02D8A4B9BDD4008EAC0C08ED33E86880D01DC0D6
              6F08268BC3BB846751869BD1EA7932B063269D011494A3B76588DA0D0A98C356
              64167E5A960B002E51817B65DC8FACA440CFC349A54B562492B91AE70F41F4B7
              8E52FF6B024710FB1A0447B79ABE053C0D770119314FAD1FC077B0421CDD9A6B
              C7104EACE2E41CBB7B3310F8C2A2AD2C6F08A30FE7CB970DB43536E1F422E1A5
              A993FFE106D5188282AA4C0185CFE0EC3A81EC07A2CC7F39001B2D389C6CAAEF
              2B60A190B12559EB91FC7F9B040E8E108B2D60821E8939003B87CFF56D542A3A
              2BC09A91246064303FBEBBA7E287B9E293B4FC489966AFBF8AB29ED2A3D941D7
              EF40FF3C42A3B4032FAF804808D1D822A6E839A1E08DED02A6408AF286F2C100
              CF7998EC37247B3C8E572A3E5D5CBC603DDA7C7837CAF57602383EC64778163E
              9A268B8BC300C9FF284059A735CA147ED61A46A900E8EB820A6D9CFA5DFC5F04
              67FD9858001680D9005F020C0099D69F1B760E5C720000000049454E44AE4260
              82}
          end>
      end
      item
        Name = 'arrow_left'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000001DC4944415478DAEC974D28445114C7FFF77D8C41B19825
              F988A6A6265BF2F18AF11D315B2BD9926231646D140B162C251636662551B320
              9485A5585148229A528A3163669E7367DE0C13B2B933537AA74EEF7EBD7B7EEF
              9C73CFED315DD7914B91906331014C001320E700BF89D23D87ADDE79F02A65C9
              B607E4562F369A2AD1138DC5FB85D904905D5EF81AAAE176D74D211C8D8FA919
              75759AF169F81AED70B7D50C20062B8221A065060F8C8933C8B792E9B36586ED
              1D0FFA935B2B6D5EECD63BA075D40CE2E46615CD8E2584E0A7C50ABD248E80D1
              D7581409C3CB3EF83D28E21E50BBE6705FE780ADDD3984D3DB15904DEC5F8CA4
              518B0300F228A8C6256CE50085D4B6D5DA9D380FAC83A9620DFE1402C992B2C1
              78122AE1671C1C5F9E21A686E259A1CB098D67886855D3338F37437BD3188D4C
              60B1A5195A452910891A930421092E553C042A5995D8274090F4EE701663F45C
              70B9A095972516AE6DD00225D11619036E3CF28223EAE91C2042FAC4E752109D
              D0EC55444AEEF24FA28BC6DE05A702B719207D4B4623FA15820017D43E683C04
              2457C93981C2CFC01BF7FED74294823898C5787E31362D569418638F993C15DF
              EE02521B69A9417A9D010FFC5963F8612930E65F49C3F8AFC2CC1F1313C004C8
              35C08700030088DF70AA0018F8CB0000000049454E44AE426082}
          end>
      end
      item
        Name = 'magic_wand_2'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000004894944415478DAD4977B685B551CC77FF7DEE4A6EDB22E
              0F9C768948B7394A190CAD6259D340D3AD8D1B2B8BB5FF242D6BA6A020883810
              9C0C04C582B269FF29ACB04D5DA389757D6C9419874EBA5644F780D636A175EA
              D0746D96347DA4696E1EF77A4E7B6FAC59DEC9065EF8E5DE7BCEF99DF3C9EFFC
              CEF79C4B701C07FFD78BDCDEFEF5517CCFAB933C7C6900EEC8FABDB000B45CFF
              0927D77772693A2F0282D2EE6CB7F5A36751AE00F18E7469FD29E6C8B14330E7
              F4C0A5F049C6FFDD31092A0F25F015E31F361C602B5EB91826291228641065DE
              1EEF327C88ABB205A015FA4EE680490772D4515BCB6E28169360E54E3281EFEF
              83103D61B258A28179FB1DDBCBEFEF6C3B4B9294B868F2D3B6D750DD3D64542E
              009B0802606E760502811088090E5E6DAA00BC486C1083886C6DFEEC9048441A
              80202BA91285AADC788E159528F5CED34D55A87E11D90AB268A653406C789623
              DB256BF8F8A72ADD73502AA3E1D95D0AD857F108745D9C028B6D14C2575F2FE1
              A1715B259E86EDA6731FD152A516013C8EDE6731643639406D78C6216383B7ED
              033E72B759595606DE95103088B1A5760714730B505EBCF4CEAF8EA90F50BB20
              B26564ABBEF1C16BF23D06DDFCADDE6EF4EECF3609370244F98EC331886D2AF0
              0439589D71C2E18A628890122895961C9F7438DFE5075B45C66D7952275B9818
              1AE6FD7306B80FC24BED312BD9BFC073F50C049830D4E9EA5198480C71C2E170
              76E076386A68F09F05BF7C01FE03C1DCBE3CA0DB2136BBBDCBE0F12DA1E40C80
              AEAE2E1E22C40F8C8DCB57880479C589E446F6C7992F06B46A7519F89716E0C6
              CD5B60B7DB4153B317AA6BB4D0FC8281E19332CCE750D6F24CA690D79000F1B9
              C5A655AB1E05FFA22F1984A098340A4156F24CA691D718C4F93588C710C4422A
              882296106725CFA2F4F24A41341A3C3ED965B09CB758B5AD26E3B06B66760D02
              5F8D8D8DFC3F6199DEBE4175147549848219CB331527AF7D1CB3FCDB9F5FBEF4
              9EAC72BF8A8B86FE7674371FBCF78B6D845739666C7C7C40A3D96BF67A3CE09D
              F7A1C45C8925A65C4ABD391D2A1F9CF9AABD4356D9B00DF9BB1CDD2F1E74AFFB
              871201602524CB9ACF1E2645A2269158BC8F124B541CB37859B259F93C2FAF73
              C87CFCCAC011DB8AACBCB5D534EC72DD0569E916A87AFAA9B548FC387A0DAE8F
              5C811FC4ADBD52B9B265FAF481787F36D11410772F1CBD82EED791750AF2CAD7
              BBF90E04791572027A7A2C5A0142980E7D63C37AAB919E9651782B917FC224E4
              F88E31E51D64AEDF2DE637A2E1E0340E7902E758626208950A2FD1C535886FEC
              DF424D8D069ED1EC876AF729A16D245D12B2FC40CCC6B288DFD39FC2396524F0
              74E09C8812F4DC85BEFE64E789A44AC86628AF31C51C1B4B9E989BA59B90623A
              3A926DD1548ACE3391D7B4105C1A8864001C1F894CB43D2F08AA4047F49C210A
              05903344210132832028B495FF0B5168809410ABAB01A8D7E920C2B2A090CB4F
              4C4C4C7490F060AE04628576D11B37616868089DBCDD4010FC49FC017F3FD2F1
              7B874CAE00092D02ABD55A8DCAA71EC6472C865023AB35994C9CD168C44BBB96
              2FA309783897100915FFEEE2A728F48F0003003C10A00EF342D8B50000000049
              454E44AE426082}
          end>
      end
      item
        Name = 'source_code'
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
              702E6969643A4242443936393441393834333131453239333441443030464236
              3142364245412220786D704D4D3A446F63756D656E7449443D22786D702E6469
              643A424244393639344239383433313145323933344144303046423631423642
              4541223E203C786D704D4D3A4465726976656446726F6D2073745265663A696E
              7374616E636549443D22786D702E6969643A4242443936393438393834333131
              453239333441443030464236314236424541222073745265663A646F63756D65
              6E7449443D22786D702E6469643A424244393639343939383433313145323933
              3441443030464236314236424541222F3E203C2F7264663A4465736372697074
              696F6E3E203C2F7264663A5244463E203C2F783A786D706D6574613E203C3F78
              7061636B657420656E643D2272223F3E1FE174B6000003794944415478DABC57
              4B6B144110AE7ECCCC261BF4E0490351F011C9C104F4A60822A248F0200A1E45
              89B9E567F8D86C3CE494FC090F221E45CC4D4183108892435073F4E2C164771E
              6D554FF7ECECEEF46456DDF4523B3BB3DD555F7FFD75550F83B479ABABAB9F95
              5267D160988D3146B6393F3F7F0E6F431D7C656565736363431D54A358149362
              4BFC1A459B9C9A9A8297AF5E4318C5C011E5305A82EC7A52C0ADD99BB0B6B636
              49B109806F694F1280C00F344DC36814278AA2EC37C526005934E9098D900054
              D5C22060B54FD6E597C9FC9DE01C389AEDACBBBA70B014B911556500C2F8CF26
              9DBFE1060039BC76F54A25A76FDEBE1B88015E0E408210128220808B972E83EF
              FBCED991B376BB0DCDA5E7FA5A65C95200E00620040729040AD1877ABD0E2323
              23A50076777775DF248E51C04925004AA81200867EEA18C709846184F7167267
              20FD521830C22D4B7DF7D381FD4F6B40150060D91208BD4631CEA8D96C2223B8
              23F063E498CE20E780FA85619881A89001C10E67851A101D06C8B1DDB3D6C185
              F3337F9D03DE7FF8A897A95729320F87346077412F7A12E4F51BB3A5C22C13EB
              62B301AD560B69832E0A0AF3406F007AE67B1E8C8D8D42AD56EBDB4AA5E91767
              BDB7B7A7C7C7C4A852D5F240EF736A24BA54986CC0F49B74F92F00C08C065084
              8C00F43B22C12D2E368C0356314D778B9580538C7CCCFE6D48E650F199D32707
              16DF97AF5B1A80CA31599A078A3A712DC200EEDCBDA7AF9CB34AD4D372CDCD3D
              84E313131A0451C2CA0070E10080CF2416CED17A7511120052BD1FF820B0C2DA
              5CD28B407606409A780A04D011616F7674AF7D62C4C74C92B23EF2C9A8870155
              B803BA44D878A2410EB205A328D4BB275FE6F369BD8B813200F4DFF8B1A39502
              7FFFB163B29ED28EF3B5224DE7050CD00029647170A49CD6F2FE834758AACB4B
              74ABD586C6D3C7D0C66BA212736AE967C6B904AED94B29B13CD74A45488E6D5F
              5D479C155A15315002C0882E312598F3C4014065B3D3633838FB156840E96DE8
              3AFFC5490CCF90DAFD4468B31E6037AEB8FB705A7C2212CEA3555189769E7A68
              32C400DBFF142DF387050FD7EE805ECD32200440E1CCB6D7D73F9D989E9E49B7
              CF9040D88484B188CD6D8A4D300EA39D5A5E5E7E81A7E18983600053F4B78585
              85DB78BB45003CB42368E36887C0A9DDFFF78A88F60B6D07EDA75584675E52FD
              CAC5FE1F5E11D1DA68BFE9F5FC8F000300558512DB698558EE0000000049454E
              44AE426082}
          end>
      end
      item
        Name = 'book_next'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000047D4944415478DADC575D681C5514FEEE9D3B3B9BBF26DB
              FC906CDADA8054546C15E98B0F2D42A06AA395FA2079A97DA86F222A16A17DD2
              07699AAA0845EC9352A1A02FA590D436606A8348B1884D71836DB56C8CCD7FCC
              CFFEEFCECCF5DC99D9C9926CDD444603DE70323BF76ECEF9EE39DFF909935262
              2317C706AF0D07C048B481F39FBF2B34D1C535B62B6CE8D08581543A85C452F2
              3D469BB5B55547C32111B62191C9E6619BD670A150E82F58E67714C1392324D8
              BE975EFD8174C97F02A0E6C7CB679275B5D5A88F44A05737C1A88EC0A86BC6DC
              DC02266217D118A9835E1581A86A8051D3804C4E2291CA20954CC02A14C8ACED
              98B6E9473089904CCF3CBCA7BB9D74172A011024555BB675900E0B9665825BEA
              69C134F36869EFC0FC480A965D076E4B3067DFC4A6482B9ADA1BC04455892AB2
              6593300BB323DF37EF78BBFFDBDBA7F6EFA503B31207F8C2F80832C919CF2174
              19F2AB6D4BFF73A95FD57B2197463E9B84B4D405E9F6661AC82620B3F3A44283
              4D4099A63F4587D56B2221639C84AD9B40B20494749E0A0F0582C45B86FAF5C2
              476015B280F9B70F64294EB8FA8CE73F84D419A6E9B3FE1FA5A14449D06A4C0B
              38F8585B53572FE2E540040F40C54189EBD0508E28F8F8838771E089C6E8FE93
              AB4188206C769F69831079C7ED8A4F42D3B077878EA73F6BBD9937A97AB0101E
              DAD28917F96014BD33F1FEA3D85E4CD14000FC3299C0F9374E63B1D047108482
              E190DAE124F181CB46FC3CF125766E3D44D97139CA7AA7E27D1E884000707277
              C69CC7B55F2FA16C32B13E682120367D163B1F38028B9F8B9A3DE9F14BEF201A
              1807D2D63D8AB81B61562A21EF295C7FDF9AFB025B5B3B54B49A144945500D25
              25C7A119E59359DACB9E922287EBBFC5905FC25505490445FC0C1B85AACC4E45
              61CBE9A50AAAE97504A101F13F80C12B181AEAC1EBB4950B04C0C1279FC3B14F
              2F4223C31A59D6496B58B820A875E0956E17E4E82819FFC631FE261D8D936402
              0170BCEB2B1C7F3647BD210B4ED647AF0F605F5F1B6E9DE83CF0CC095CD0C933
              B7EF90F101327ED231FE3B09350EE2E3BF520997C7BC2915E4F81870E5EBD5C6
              03AF844E0A3AC67D00691592C13E5CBBDAB3DA78D942A40A4851FC7794ECF989
              CEFEC6037E37CC5F780BBBBC2F8FAF34EE03E05C099550A2A9209F095DA7A7EE
              03E0740D4D893A23D134E1EC71EE7651A614484F58B1173800532493EED080CC
              4AE33E0093EA7562761EC9D169E4F26AAAE1A8AD6FC6EECE97557BC7DDBBF790
              37C748A78686CDCD6868694774FB2334A66D76B56861122FE798E95CC673946A
              108B954632DC99507FA0406A741FEE902833F327FACF7D420A8D658564607266
              091353F318191EA60253DA7ADDF068E4954D215574B6AD89370E80D8A25176DA
              B1A5EB624E6E652B075E79FFB268701A4ED7486F07C007376ACB1E7EBC3B8EB1
              7C3D4EDD88AC3B23A291859FD632A6AB2B2AED1DDED307F6E86B678F4D67C51E
              F5D212368762A70FBD5F69C22D598A6CB35EDA2D5502A07A58CD8A4945C5A491
              A4DE7B57449A53B57B1DF3AAFA6EBA12E8FB25B3E68DD44572149559F8BF2DB6
              D1FF9EFF25C0001276B5884636A3630000000049454E44AE426082}
          end>
      end
      item
        Name = 'book_previous'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000046B4944415478DACC575B685C4518FEE69C99BD65B7C926
              BBB16EE82568D36A10AD2521A804A94AA5496C2D42DF44F0A50FB55050287D11
              A4141AC568519F846205F54D042B2A569BBC2AC6045351B04DA8B93435AE4DBA
              97B3E732FE33E7ECBA89A9AE75439CE5DB397339F37FF3CF7F99C3A49458CF62
              609DCBBA1360B7FADEE71F9EE9B62C5B3283B508933F2484E8334C766F242C20
              7818B97C0E4B8B375E62D4198F475F888478C48344A15882E7B8638EE37EBCE7
              A9675FAC9580F861F883694BF2B4EDB980E7C1731D28FB61D206371C24E23134
              269310B114C2B124C2893416167EC7ECC42768492620A249F06813C20D4D2858
              124BB902EEE8EC89F31A84F38EE7CF5D6849B274BA7D076CCB826B5B709C125C
              876A7A765DDA1B11738994E1AADAD5E3AD6DEDC85ECCC1F512303C22ABFB1D6C
              486E44AAAD49AD1DAD85408CF1D0039E57004209E4E77E221245D8A53CEC625E
              D78A4028DE4C3B6FD62F28CD789EAC3C57FB996ADB569EAC4F8B366E6A844F0C
              55EC23AC5F24B543BA81D91018BD6A986054FB6075F5022118E6075ED5E4C301
              757DF6BE7CB6C28ED92DDBF36A0444FFCB983C70CFED29C7D5ED86B2EAB00641
              6B2501D13788C97D3B5B32F7DDF90C2C47F785FC2175045EDD09F065C269E7FB
              77A533DB33BB2159085B53AD3874C618F7E4411C1FB5E17CE39212140949D61C
              C260D7E9BA11D06ADFDF7D5B6647660FC67F398B873B4EE3B9BE6E18CAC02AD6
              AC7E0E1A453F9E7CED70DD34201E3F8599819E58AA73D300C6A7DF86494A1FB9
              7C0458E5C89519F46E7B9088D5EF081A688BA94D1BDBF1E3C2BBBA67D9DAF2AF
              8F7977BAAE46C84B8B18FEFAE7094861C1103E2D4630481346F84F9801727206
              AC8E04AC2F4FE0C8F9AF30323547E71109041344948240CC8720F0A88F029BAA
              9B47AA23A0188B999153384AF5D0238FA177CB163FD6BCF33E4DE0DA01512497
              B4091475E1CA311CD8B5B76E0494B7675543939018DABD17BD1DDB2800D0717C
              7A0CFBB61F3BFFD167FDD3D87CD7FD58CCCE522C2FF8B9C02AD4CD0DDD0A8941
              1CA5DD0F8522E8E5FEE85575E0DAFFD720125607A20A8961D2841078B3A1193D
              CAE8CBFE27A5BBA604AA49B02F4EE050E079251D88752EF0F04F494F65C5322A
              6D54F5551660AB12A826510CBC24A1A7ABDB0F2B0B40056A1D95D40DFAE3DC24
              7070521FE7A242C0300D980A6A8C609A5CF7DD8C0002C35C2ADF077CA144C064
              74DFE39024487A06A443A0BE42C9C3D2AF59DC989A8755B2F55D21DE9846D7A3
              077506BF74691A25E70AAD61A2A9398DA6D63664B6DEFDB70496070B22303573
              1DDF4F5DD00BA2A2E272AD2E246A802E28F4ACF246E1DA6F38F7DE5B3425ACB5
              A3A7D12D69EEDA2266AF6671716CAC76029CB4359A6D80E5D57E8B975A9E4FD2
              50DA5B9958246A262059313B7AF2DB0D3BFFAD85BFDE35892BA546BCF25DF23F
              7D176C206C26A4B48E6BF4AECEC3678FCF1779AF6AB4469C9189379E3E19D856
              B92843BFCC6A74D5587037AC3507A9B92D84C6A07D9DB0A0F24ED51CB256E418
              D6A69855A41108CE072EFEFF2A6CBD3FCFFF106000A59AADB40C6D9131000000
              0049454E44AE426082}
          end>
      end
      item
        Name = 'bookmark'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000044D4944415478DAB4574B881D45143DB7BAFA7D66429C24
              86CC4A71ED2A0B0312507099D90851102420BA511044E3D244C84614C4E04A83
              0B8504CC2290CDF841080882A0107463760AEED4E0CC30939979AFEBE3BDD59F
              D7DDEFD39509D6D0AFA6AAABEE3D753FA76E93F71E6523222C68FAA7271EF972
              5F0FCF3A4F50E431307B374EFDFCE70BFCCEE0004D74EBB692672E7D75D342AD
              092E45020AC858E1BD7419B8FE3C9E7CF3220CBFD33CFFCB0717CE9E7CEF876C
              38DA817276B1365EAF58A0865FBFF5EEDAB325E83680A1287FFFDC29EC8F3258
              E3F0CEF5DBB872FE0C76FBBCE39A851DEDE3EEC5F3387EE94364C6E2D3374EA3
              B7C73BBB003082542BBCF6F1D76BA2879FED5900066216633D3EFAE60E76F78C
              D80963EEBEF8CDE145FEDF1903EAF7432FEFAEFEEAD0DBDD022D00204E76FC73
              EEE45138175C3E980720048165615A29E88482D96CCD1D948D79970EBDC44CA2
              78A88A8D737D9DDBDB4CE2AD5AAE676DB08C32282BC6829AC248022203E934F4
              086BAA370BFDCF31CB5EF2D3913D6B75005008A580BC869B15AB9443490004D3
              FA605EF27374D364AB99B166A6058C6BAE0CC3E2B4CE880B52783362A0C01E4B
              356327669A52CC1E444FDC58A00840BB00501D00D5011583E002B6C038C398E7
              3F399DF0E4B1B9D67FEBDBBFD1D734F360D2D4CC18B0CDD3C8E12AE492054922
              8BE0177BBECA80BA9C6E17508EB42EDA78D99914E6C94216B0DDD9C48497BE67
              40DB1B0150DB0562FE433D558D2DCBA19818B03567C94657CF1EC70A390845A1
              BCFBFC6911717CAE05DEFEEE9F89DC98200C87B4BE9158E21109285FBA808390
              AC610E20BCFE2373C6CEE61411C96EE1889EA2C021AE90139705BEE982004795
              11C969A892BCE7A9419AA0DF4B1840471AFA663C2C76410BAA1824A95889394D
              5C20AEA09C053B99B0B048BC0B9C6F30A6E73FA526FEA04457F6142B9434BDA8
              39CAE54459C0B589C8E54A02206B020F481F08BABC23A8F336868F4E433B1D03
              6A72317016A4555227C102D455CC4C71C2C2BBC0B438D397C124F4CABEF73A09
              3D01D116100FBAE820AC9769322E524A4877F3DF0DFCB5B1891347568250998F
              89015FC8E9A4E29C07DCD46E519EDA0CB7B72DAE3CF56AE865AC8A5A32E699E5
              0335FF36A446F19832D16C3DB48A9BCF5DC0EEA38F877E6B65159AE7134EF232
              1BE63D09C5C68004BAF58D22C373F8A64CBDEBAF5CC6F2D2619EE7841A0EB1FE
              F265ACDA516EA2CE1824D42BF08E7AC0B582904FC841D77FF804F381CA534A9E
              A56198F75100F2208CAA076CEB3674CC228A951C5E39DA8C363E91128A8D4841
              D9E73D1DAC222ACE8BFED2F2143F08BBC4E8C7FD30611B802F08A7ED4302A24C
              5F5E4A514158BAA03927E5B7CAEBEB83B632155BE69A06C00BA4D295EF01B982
              A54FB8AA19907E50FDD02C47A90E00ECD39D3BBFDF3D546D62DAFDECEAAD00EA
              411184C390DF694CB7BE8E57B87B8C9F23F1DEBDBF0F627EB880C41FC2EAA2BB
              0D80AF39F067307AF8FF1A7F58E09E14F8A2FB3F0106008D0AEC141C30B93300
              00000049454E44AE426082}
          end>
      end
      item
        Name = 'document_insert'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000055D4944415478DAB457DD6F1555109F3DBBB757CA83FAA2
              DC9AB4B7A598100311BFA3B6299818E406680BC46A94366A30582CC55A3581A6
              584C041EFC482025FE03D6D00F1ADBDA48A46AC383BEF0E08B0F2680911763FA
              717BBFF6EB1C67CE9EDDBBB75FB9B7694FEF74E7CC9C3D33677666F6B71AAC3C
              CAAE0E0F9B879B9AE0CEDDBF8131061A49E99FF01608352DE057D0FB73CE39C4
              AB2A617064048E3437478D551CD8EC3386C140D775307496372804121A601A4D
              027E393DC9384E5C9703FE0A6CACE640C43F0A630644D0818FBFB901B5353129
              76F124EF2776C207FDD7A1A6720BB427764017F2DBAA63D230E94FECDB095D57
              AE436D3C26E7EFBEFC18DEEA86E20191D51C0842E94580C1A5937B654C0517A0
              699A545F4619C7B98B5649CF484EA7451957328A00CD4DDBC17B58E1DE50C4A0
              08D02368FFFA07D85AB505BA9A9F82F62FC7A0B6BA42EEE4BA02654FC289AFC6
              F33234D8D5949739AE0B1DFB7701D739143B1EBA3A342468CCCCCE8A85857961
              9B69E1581961E7D2C2C52B477250666653C24419E949E784E4969A139F4CCECB
              BD68D0DE64A3A808188C125087631747615B4D8597742A8C14FAD3AF3E0F6F5F
              1CC2E8C4E0740BF21786F1D4311985336A1EC73CE93EF40CDEA3951E81543A25
              72B92C723692A30879D71282AB2B11C9B84F569EA7F5A8CF663372AF9223A033
              AF045BFBBE834731027E96F71E6D80D67303508D797116F9B6BE01F9BC7D5DDB
              B90195130036E640CFEB758B3A439111304D4BD8169D14038E292FB88B3F47B8
              8EE3C97C9EBB1E15CCF3EB2DCB927B8523403561BCD43731B1E7B34912942D1B
              016A409AD74CA893715562F427653ECF45A18E17AEA7D2A5BD0AF20B691307F6
              CA272DBBC1B6C7CDE94F13519459B2FC34DF01DD2FDB60686B9C0772CDE3C89D
              FBB8E0309775A0E37003D4F58E9B7E248C90B7DA3A51D05B940386EF4BC67661
              E48F3938D6548FE11A376FF6251E49CECDDC1819BDB6C7758B6F1EC5353606C9
              64F22615B2E19FCE7400CAA30C26FE4CC2D1030D60C3E4BD375BF7EE42D5FDC5
              76CC12065A83FF9072C1C6397CC8D108251B93BC1A3348FFA847B59E832CE490
              B2810316D76053B44C26DCE0D8CFF07B5FA26E6C7468D216FA76AA6BB14E9665
              2E78D8E2B7E6C6C6170D3F216DD0A1BCBC0C6EFD3A0D5809F5289EC5EAD8DE78
              F0206CC418BE76ED59BC941B5E463270F408DC9A9E82A9B3D2F86D0A93CDBD73
              DFBE7357D6F0BAC41EFB4175BC4A5E714455128AF4F48F3F6D9EEA0D8CFF8BF4
              805A241F8B2C1B4D2B8060B04AED8B453211A02411D66BE480F5CBF996062B3D
              AF237F4F19B7C29B1886213B18F505166CE66DA8A96E45208529F815D633A5F7
              209990EF89B08BE440068DFFA5A419DF78D84D8A40048D7F7885205745D0664F
              EE7F1C3A2F4DCA975107F2A72E4F7A2F1F858802599C000987F7F6ED00E1C212
              446415185DF66DC824F57726BC7782826434FA4F25142403A90F43325F466BC9
              01139B9D58F4EC8C623B1745E138C22B8264DD879E86E35F7C2F41870F50A52C
              0CD3D0816E846E9E2C261DE83CF004F012EA39781DCFCECD89542A29A1956B67
              116E211CC3AB402268664938965150CCD385E5740FC1B58585A4DC6B0D90CC90
              09F8CE859100904008929D79ED0578EBF341A841F8DD43FCF9210F8AA3CE9FC7
              2B1F868F8E3CB73648964ED369720A8A613E0B57C12C825CEAEA2AE8C597215A
              8F7A339B15E954BAF408302A3F8320D98002A50A92B5EE46D9B71E2443BE0DF9
              AD98035CE9685E2BAB06242CEF79A33E780D97140182528E6DAB93AB08E0C908
              662DE197CCF3EB6DDB927B951E01E6B51F4E75A5E5BF3CE5C7A79BEF6C92D716
              E942EBA94DF98D6B25E4141E0F2255ABEB468C596AFBAB3950A6BE90231BE480
              8D94FE5F8001005F6152D2DF2CB8940000000049454E44AE426082}
          end>
      end
      item
        Name = 'document_next'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000005654944415478DAB4575B6F545514FECE99694B050206E9
              CCB453BC0462D448D2CE40DB994E690442286DA130B62989CFFE008D8D91A0EF
              1A634CF09507C3A59799CE4C8736DC5422C6F8A0C6CB834413A086A48369690B
              85762E67BBD63E979EB9D00EA4EC64CF59679FBDF7FAD65ADF5A7B8F228480A2
              28CEC8E8688C844342D320F0348D5729501505B95C2EDE1B0E876920BBFA3221
              D56D240062AD5A2A951267CE9D8BD2BE8ED5F43B8DE73A03086EDE9A04541A76
              56E94FA865584F5ECBA5F14ADD567C7DF62CDE397E1C6FB5B7F79C1D1CBC7ABC
              AF6FDF4A9E300128A6DB550781AE5887CA6BEFC3F9D75079008486CCAB6F03FD
              A7A1AA0ECCCECEC1ED76A33D14DA33383232D9170EBF48B3322B01B09AA29242
              47152A48F90BEF7D47C6E5B0222914891A773FDD43C269A2918AEAE7AA313D3D
              038FC783B660D0331489DCEA3D76ECA552208A01D0066406E9A4271172EACFCB
              52C74AD473BFB19F9ECBB3AA2A2B89551B2C4FEC696DAD258EDD39D6D3535708
              A20400185B6912C8961DC1D5434061530C37EDD8BE1D67CE9F977BF088464630
              27A86DA5BE9EFAEC6300081B802CC46BFDF8EFB3768E49591CD05EEFC7FC230D
              BB7C0DB217D1542779E5E34360C4996D51B40CC4BE2F200E9C2A3B0B945C060F
              EFDFC3C3B99CB59999591E8F9B5F501E091556C90CA05069D9A2800BC8C2952F
              EBDA205402EF705ACAD9FD4288B2EA80D55472B94A1B5DBA380197CB9D67093F
              FD7E3F2626C65153E382CFE7B364FB37578D9B5CAEA1A1A181ABE29301501C64
              050138D4D9695967B782E50EFE66BCF33C7BEBECEAD28342D6B3727595109608
              01D57362FF8564121E4A21213946E46A6A42726C8CACABB1644E3106B46BF76E
              EBDD0C0793AE913C6485E8490070EBEAEED68B12C7D6F0008F19879794EDCD7C
              37D79B1E782A00EC81E458822CF2147160777333C6E271B85D2E5D4E24882B3A
              079A8C77B7DB4500047CC409E6931D58799590E2D67DE4A83C5A59B70E4058D9
              7AF8488F518305BA0F1FC95BAF7FD3D7082AE34E553F102B1C4AB959A0C041A8
              13B151D4D6D64A256C4D73730B6234C67166394E32D77A4EC5E6267A8FC768BE
              C7CA57416B4281167C18F903B19FA7F0D55E65C5FB40CD702422CFF2F9F9FB62
              61E1A1585A4A8B743A233BCB8B8B4B799DC796E89949A785C8656865B6A0EB63
              3B0712E2EADFD3C27F629C15D5945507385ED168547AA03005038100229188B4
              BE3518C085440C13539B70FDF6922C6266C563D9413F55E4FADBD38BF8A8D78F
              CF9DE3A9EF3FE9A08B06D256C80D56B30752E1A34741D6D3D9E280D3E9CCAB03
              85154D9255D1EF0F6F0E24F1E5BB212EF8D2FDE63AFE9D5EC8E0D28D194CCE3C
              42BFDF83D3177EC5B71F1FB440147BC0A1CA423432320CAFD76B290F04831819
              1E965E31E56DF55E6CA8548933C0BF74068CFE9E824E7A25EF6465FE6D5A5F8D
              F11B73E8DADF48065E5CBA72E2800451320DB9F7F6F5E5E53483E031DE950B13
              CBA6321149E29F790D5B366FD4EB9EB27C57E19EA3F9E66D2B79E5177C73F2E0
              4E4E8C92005445BFD90E0F0DC15B57679DE9A15008433456C7637A6E22D4D686
              B1E83002DB36233EFEA3B4D49EEE4E42430E42635B8BAC2DBFFDF013B9BFA38D
              3EDDB32E26855990265667B3D935BB21370CC4C507D71F899693320B8828F0DA
              EF05C51E50F52C384FB79AFAFA7ACBFAC2F7C1C141C911DD080DADAD21F21A8D
              D11CBD7C6BC495103A7DF588C62FE3D45E0D74BDB943D3EFDAB3A0C8036C3D29
              116BDD12F1D132EB80E101BB8576AB390BEC1E28E511FB1A591768BF744EAC52
              09A351F12C1BEF5FCA03AADDF267D91EB7BFD3F6FFE2413416DBA01929B666CD
              486B0AEB83929F8D52BC99E497A93FBF5C46D6B40923F76F16FE2F300154187F
              1A2A9F611438F5160AFF19FD2FC000263BF9B88D3FC3D60000000049454E44AE
              426082}
          end>
      end
      item
        Name = 'document_back'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000057B4944415478DAB4575B6C145518FE66F6524B2120D4BD
              7525D1941034D6AE5BBA6D7717908B44E8959642893EF8ACBE78232684883121
              511F7CF1415F785058DAA5DB6E5BDA204AB4F112E3256A78D068E2E5050B56CA
              82B0BBB333C7FFCC99D94EED747725E52427E73AFFF9FEFFFFFEFF9C91186390
              240996E21A1D1BBBA26ADA6AA66960B89DC2BF9220935C5555D3FD7D7D7D3451
              B0DFCA161DB1667864842D579999996127138914C975D89DEFB499739BA07EFD
              ED0F40A62DCE2AD142AE407BB29A9AC7FD75F7E0BD53A7F0E4A143D8BE6D5BCF
              FB8944F2898181FDB4412D07A06876D941A05D77C1FDC90B70FE38541900A641
              D948E70C9C802C3B3037770D3E9F0FDBB76EB505E12C254B92E94047155C7478
              EDF31F93722A4A9242D251E3F21B5BA97382B825A37A45356667FF86DFEFC70E
              B2446268E8C2407FFF0E9313A50190005283CEA49608F9E7C5F390CA50CFF7E0
              2E6AE77755B9DDC0AA95564B6C218E5DEAEDE909D0B25206000C519A0E64DD86
              68791790DB24C34C1BEAEB71F2F4695D069FD14809CE092AB5546BA8CE3997D6
              C5045000DB34802B6F6EE33EA98803DA0303C8DCD2B0391CD2EB229A0A92BB97
              7681E167AE8BA429603BDF02DBFD76C55120A90A6E5EBF8A9BD7D4A23033B2FC
              7E1F1FA032124AFC48CE0085E416168164309298B52F4E039309BCC3593C9C9B
              DF26E794062093C96512F4C1B92978BDBE059AF0B6A9A909535393F078BC0887
              C3C5BE75CDEBF191C9358442219E15FF1F00C9415A1080BDEDED45EDAC5AF0FE
              1EBE668CF93E6B69EFE8104E21EDF9E1B28D0BCBB880F239B1FFECC404FC1442
              4CE718912B12C1C4F83869E729F6798871409B9B9B8B63D31D9C748F9085FE73
              E7540680978ECE4E9194B86F0D0BF039F322E37D6B31C7E6F7A6052A06606E74
              7022D1C113E363A4917F11079A5B5A309E4EC3E7F58AFED81871457020628C7D
              3E2F01600813272A06E072888DD56E170A4C4257F73EFD637EB600C08AD1DAD5
              DD63E46086CEAEEE0572C49AD50295DD8658E596B0E9C50974877D38DED78033
              A911F8FC86054858A4A51523A3344791C1FBE951B1CEC1B5D07894C681805F07
              C674B7691415CDB04560139B9EA62393ECA39F6759C3E1715A56A9162C552179
              54558529B91CCB66732C97CBEB6D366BB6E6BCA257DEBF71E31F96C95CD7DF08
              C9E1617EA8C7CE02EEF82B9333CFED6BC2EFB35954D16D1C7AF92C544D241A33
              43D210D17BDD78F7995D181E4CC24BFC686B6B432A95D26F3DAE94180FEB63EE
              8208458B1D0724CB93CCFDE8B1A9DC537B43487C7D09EBD756E3B18D6BB1AEC6
              55BC8185B524DD94CFBE338D8BAFB7432DA8FAED67CA996FA127319303854241
              6F6B6A56904B53D8DFDBEBA5A5CBA605DC3B5F3B97DBB3BD11933FCD61754D35
              E6720C89EF6745ECB3F9FC4B84464F83174E12FEDD979FA3A1B915C9C121D4D5
              D509CDA3510C279308D0B8783B700BB4B688EB7D0912BA3E3CB2BB417B75EA87
              FAC687E8DDA11A612883595E48BCC3CDFF4B463C561B23517DB2FFC001581FB7
              FD070F1AE49BB70AB740A928A0DB06572F1C7D7C0B3B3639FD7034A2A3FE76FA
              0BE4E944C101E392A1E62B3279A896E11BB24056D1F4BDB1781C4343C21266B4
              98739C079C1392A6958C027E3F07A9C65B8F4EB2973EBDC54287D3CBF63A5614
              85E5F3F9925190E7A4E0408EB7E5F174FA3C7A37AFD717CE240749B3A09ED1A2
              B118F99CC6C1A07ECBC562710CD238180C16FD1D8F2F9CE3492846DF69652C50
              CC03E9B4F82FC81A8897A31008463C289B0704215401AACA259697D23010082C
              D0D64E7BF31B6E814AFF8C3CC9548ADDC9C2E59B16B07DE4F137C09D2C56F9CE
              25FE2F6EA44647576AE2FA5BBE9325F1C39AC9643E33D38B64F377BC86EA7D54
              EF064AFE87DC6EE1AFDBBFA8D28F27AEDB0170193F0DEE3BE401AE7996EA2D0E
              E65F0106008B36278EABAD378D0000000049454E44AE426082}
          end>
      end
      item
        Name = 'text_document_wrap'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C0000045B4944415478DAC457DF6B5D45109ED9DD9BA4B682A550
              13106C24D527156BA3A522546CFB604269728D48A052FAD097D6077F50DAFE01
              0A8582E0435F44442134068968FA608352F1A10541FF0169EDABC116EC49A5B9
              E7EC38B3BBE79E3DE7FE4C4D7561723927BB33DF7EF3CDEC1E0400F3D5E2E2D7
              5AE184250219080F6650F855889059BA549F9A3A6CF8799304DF77F01090CD8A
              E0B841D1DABC46A5E1CAE56F2624B60018929D4BF0A55FAE8356213AA3A4260A
              5C5754744C7AC3CA7F330B30B9EB09086C0F99DCBBFCA96904A394400475FB26
              50B2924FEC7B881F7A681BD0B651A69A0144CB897DA5580285265E2CC18D4607
              C0AEAEC0747DE6BE33B0706919D4F6B1C0280506D87756DE90890912718809FD
              A9F5136FFC7E931F515E754C85EC4C6C74C7E3F0C5DC1CD4A70EC3CCC4015858
              BA0C6AF849D06E3139180ACB0251717E34EF5EF10CA5B150AC6345C360AD0643
              83ED6D70A0E6E6C8D03CDFA604C96A0233930721FDE33771E2FC886F1DF9AE30
              002506F2A1D971CD68F864E957768E8E8DEAEE33A6F5D8E4B3CD775B1EDE0CC9
              9D55B8FBF75DA8BFB61F16BFFB01360DEFE4B916A84262098050652A007C4084
              13D3E31D01A40CE0DE5AC33DEF1C1B83B98B17DD2EADB570647616B2BF56408F
              3CE579EE0440C4EE0204CBC5AF036D17167FF6026DD1810770FCD0F39024098C
              EFDEEDAC3C23A4D5B2AF10AB23034E30A8A242F16579F2F53D0C40B515A165C1
              72678346630D6EDDFAD30548B9E0858191E147836FF16321EB96022F945CAA54
              30C0A03E5EB8E60020B6AB82309BBCD625F889E917214DA30A539E3DAA30D853
              84794ADE79732FA78201F4E88A02206300F71ADCD635967C0B9384D40580F600
              CA0BB5A3EFA3F9AB0140EF662C004ED6F7808D26FBF2C3CE55200B4D6000B1A8
              55D9BDA4E4BDD9973D801E08241D9E8194DB30163D467CA2E7AFB50F50AE019F
              FE920651393B3FF7936B36FD0048B30CDE7EE3A5D25CF1DD3CA3A2986D35E06A
              BD09CA77C7536FED730CF4331C036B29A89C6FF2BEA90D7A134377AD187CC01C
              A8AB02B6739F5FE1D3B23F000D06F02EA78CA21418F6612948386A04250D6897
              23614145C7ABAB4B3873F455CF633F32B49E012CB1EBFB407B0D4041B7D0EF6B
              3600E05D2BB60F3FFB1E0C9F09FD54419A66F0FE9157C0567CBB3E40D0BD0F78
              06220DA0E7E0CCB103F1E1D96370C7E32A5058D600742D43F27912E9FA9A0DD7
              2BA65D58F8E0D3E57555C1E9A3FB399C6D36273947DC8D93BA9C053E4F50200F
              0CC88977D63180FD692074C3163FD8BABEE530C20080A23EE0CF7CDFC93B5E77
              AB10A838BA9B02476C595DBE92A90040C5171205B0CE8B69F37A1A33203E2917
              21751361F11BB5C37FF58990FBEC2CC270E13446F98B23A31D796C07CC7F397F
              7F9BAF60175F8E01931F66D89482C9AF5DDA181888563DFDDC383CB3EB850DF9
              44120DC9E504C897B1C4CAF56142E9243F2E7FBB852C9579DBC86FB4D8B5BFF2
              25B9F747D846D9B63EC0EFD276A86ECB6787FB2263DBCC3600FFED58635B85FF
              7BFC23C000A4458D781EB456A80000000049454E44AE426082}
          end>
      end
      item
        Name = 'vrule'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000001514944415478DAEC97B14EC3301086EF5CAB2AA1858599
              17E109100B334B25065880B5803A16896E0C6180A5626341CA020C0C9DFA226C
              950A42A522853A67CE51DADD5744169FF4478E6D9D7F9F3E0F87D65AF00D44D4
              FBE7711245D14E3DAAC1FADA2AD4A3EAE3F1DEF62E2F1BAF9C6EB3AF381ACDB3
              6B4BFCF3FE95D9C90FD9F8FEC52D347C732A9045CD7D9AAD18AE7A0F30FD9E71
              325ACCFB84161A402282CBF6010C476370E3A2EAE89B485A013ED4823119988C
              40C2D1D206FE2AC4069442D0BAC252FC2A54190614B43A37903CF57333D2D072
              0608BAED4318BE8D731EFEBD020B080DCD9F6080304018200C100608038401C2
              00614910561C84580E84A79D5B489EFBF958EA412F53BEBBEE117CA404558DE2
              A728356067E9647072D1DB9A37A798A50337EFDD6209BB63D7846EB2368A4B18
              D688F5CAFAF4C92935E00E5D299A512C6E3E65A5BEEDF9AF000300E1A1152B2D
              8C740D0000000049454E44AE426082}
          end>
      end
      item
        Name = 'font'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000001974455874536F6674776172650041646F626520496D616765526561
              647971C9653C000005E44944415478DAC4566D6C5355187EEE477BDB6EBB6D77
              B7E1C618636C638C89C036D8071F667C4454981063F48721C46808269AB00430
              98A082467F40087E8628011333FC5A6286A0D11F84986846C8405705826CEC7B
              30BAAEEB6DD7F6F65EDF73B7C118746C30E24DDEDBA6A7EF799FF39EE779CEE1
              0CC3C0FFF988ECC571DC54CCC5AF78B3EE255DB41DB25B45C80E09BDDEBEDDA7
              DE79E65D1A8B8D0B608A1E49E3AD070F6DAD429A4B427DC3557C5EDF359B7EB7
              8C07809FA2E242C5F6DABDCF2ECDB74520E0F0191F325364FAD5B298C6ACE3B6
              6D8A00D8129CC9DBD61667E3CBC63E9C6E092255B68113A5990CDCC3062054EE
              FCE6C30D15F968F3EB68F36970881C2B0E7ADBEFB5CD0F0C60465975B2A2289B
              572FCAC6771E3F24818345E0094C1473B3142CDCFC7E31E3F9C30260C9AADAF4
              FDBAB27CFCD61C841A316011790804A2CB1F838DD4C0F18232DE363C0800AE64
              CBC1F2BCECF4650BF2D3F17BDB2044438785E7CC601D6044949CD3963C2C0056
              9B92F5C993A5B938DB1141C0DF8F583844AB17CC0E04A81B190440901C25E3F1
              E07E01F01535473715E566CC4B51DC68EC8EA0B7BD19D1307581562F92B1A911
              1D361B115114B387BD604A8D4812129403EB97CEC31FED8388AA01444321E81A
              B9004F6B227B370C0E9223119C60499FEA2D102A77D4EEA97874967DD0B0A03B
              60E07AFB55A8DD577E0CAB2AB59F48C8BA40256F0475B8136D28DCB86D563C25
              F0F7653AB25253559C87735D510C06FC507D37D486CF5E3B10A24E88D4019E42
              A06DE81BD4F188E2842365465EBC5A9305202CDF55F7D592A299E8520DA8E4F0
              DD6D2DE8BDD4F0018D5D8BC562884422435D2022063502909C046B9252166FBB
              27052063D19A64D9E5AC5E543013177A35201AC1405F5FF8CFDABDDFD2B04F0B
              072FC5226193842C7C211D69C94C09F6D2A90060C97DEAD553CB17E6D3EA39F0
              1C8FF69666F85B3D1FD39897221855FB1B077C3E93883C01E099195B6C8C8871
              95C04FD8745ED95F9EA6B80A676765A0955C2EA685D1D3D9A19D3DBCE30B1A0F
              5084C303DEBF428321F002E30101A0D9655926378CAF8489CAD0EA48CF3B56B5
              781E5AFBA3B0109F3D172E221A33C465BB8F7B3893E00674925F6060606855C3
              1D084475A4120F9812FEAEDBEF35FF3849007C25994EE634255D76B971B13742
              12E3F0C2EA12F3D0B9435CBA8EF33D11CAE2CC4A2A7D75263A4694D038F67232
              11009298A81C585E5A846E95DC8D042E52E14E951518739F34980719E659A019
              43C8342A97E2926195939912EA260B4058BAF3D89E829C4CBBD596042D1883A7
              A9091D1DEDD4611E775C67A9B816D3B07EDDD3F45533C168BA01B7CB09C1EA18
              514278C2007256BEA83864774DE9FC02321503C160109D9D9D387F64E7F3BEAB
              9EDEBB29E5F1B78E9F6485D9A1A4D37670D40DC9662725DCFD4C180F8038BDAC
              FAD0FC3939D00509BC4EC46BF220D87DF92815677BD93F9650F4B869D9A180DF
              6F773A9D376FDBB22B29AE12E2C9905BBCF5A372D9E9AE9E9B9F430227A17B7D
              145E347CF6FA3E1AEFA4E861EE3726BC7A74B0CDB4E29B52E4867890ECBCEB99
              100F805552326B579417231263870BD0DAD68A6B4DA777D1D8758A509C3C2D12
              F09EE9EFF799678119542F467D4A70D8E9926C97EF05805BFAC6D74FAC7CBBFE
              C48A8AD2E98ADB09923142A141FC7BA505A2E4E8A3FFF8E3DCF3B99297F7CD11
              ECAE429E38C04C68C48C880A9896AA2031AB704B65CD9192D120384618DA2BEB
              AABD3F85D35214B8E5441415E442A2FB5C283AC2EE189AFEB9089F5F453F194D
              D07763CDA9F79EFB751407CCFC54CA772525E0B1A202322592A93E52853A6003
              CE792EA3E77A1FCDE3C7C91DAB241A898C90D0418C0D6F585B2245E98CD15850
              B24D1882CA7302962D298448FFAEFFA51127B6AF3C3FDCBD914E24B0856C5C5B
              02961F21E0BA710B1D37FC2A5D904B9756E0879FCF9A39A301584936D2A7474F
              22C63261DCCEEFE119584B05DE24327BE9A3E5C7881737FF8E39CC9DB78CDE02
              1793BD29A37B3F8C07CDC39FB7E407CC9A60FE6D73DCE4C0704B2C134866CC50
              59FB46AB6612F9B7CDF19F00030013CF30311CB114EF0000000049454E44AE42
              6082}
          end>
      end>
    Left = 360
    Top = 192
  end
end
