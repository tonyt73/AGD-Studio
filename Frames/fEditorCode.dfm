object frmEditorCode: TfrmEditorCode
  Left = 0
  Top = 0
  Width = 892
  Height = 731
  TabOrder = 0
  object evEditor: TLMDEditView
    Left = 0
    Top = 0
    Width = 892
    Height = 712
    Align = alClient
    TabOrder = 0
    Document = lmdDocument
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    CustomKeyBindings = <>
    OnStatusChanged = evEditorStatusChanged
    ExplicitLeft = 256
    ExplicitTop = 240
    ExplicitWidth = 185
    ExplicitHeight = 89
    GutterBarsEmpty = False
  end
  object sbStatus: TStatusBar
    Left = 0
    Top = 712
    Width = 892
    Height = 19
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
    ExplicitTop = 627
    ExplicitWidth = 783
  end
  object lmdDocument: TLMDEditDocument
    Lines.Strings = (
      '')
    WordSeparators = '[]();.,'#39'"-:+/\'
    SyntaxSchemes = <
      item
        Name = 'ASP_JS'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          ' '
          
            '    <Scheme name='#39'Main'#39' defaultToken='#39'htmlText'#39' inherit='#39'HTML.Ma' +
            'in'#39' allIgnoreCase='#39'true'#39'>'
          '    '
          '        <RegexBlock innerScheme='#39'JavaScript.Main'#39' '
          '                    start_token0='#39'tagOpen'#39' '
          '                    end_token0='#39'tagClose'#39' '
          '                    defaultToken='#39'defaultEmbed'#39
          '                    >'
          '            <Start> '
          '              &lt; %'
          '            </Start>        '
          '            <End> % &gt; </End>        '
          '        </RegexBlock>'
          ''
          '    </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'ASP_VB'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '    <Scheme name='#39'Main'#39' defaultToken='#39'htmlText'#39' '
          '            inherit='#39'HTML.Main'#39' '
          '            allIgnoreCase='#39'true'#39'>'
          '    '
          '        <RegexBlock innerScheme='#39'VB.Main'#39
          '                    start_token0='#39'tagOpen'#39' '
          '                    end_token0='#39'tagClose'#39' '
          
            '                    defaultToken='#39'defaultEmbed'#39'                 ' +
            '   '
          '                    >'
          '            <Start> '
          '              &lt; %'
          '            </Start>        '
          '            <End> % &gt; </End>        '
          '        </RegexBlock>'
          ''
          '    </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'C'
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
          '        </Regex>                '
          '  </Scheme>'
          ''
          '  <Scheme name='#39'Numbers'#39'>'
          
            '    <Regex token0='#39'number'#39'>\b (0x \d+ [lL]? | \d+ (e \d*)? [lLdD' +
            'fF]? ) \b</Regex>'
          
            '    <Regex token0='#39'number'#39'>\b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? ' +
            '\d+) \b</Regex>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'Comment'#39' inherit='#39'Text'#39' defaultToken='#39'comment'#39'>'
          
            '    <Regex token0='#39'st'#39' regex='#39' \/\* | \*\/   '#39' />               ' +
            ' '
          '            '
          '     <SyntaxBlock capture="true">'
          '        <Start> st:/*  </Start>'
          '        <End> st:*/  </End>'
          '     </SyntaxBlock>                '
          '  </Scheme>'
          ''
          '  <Scheme name='#39'String'#39' inherit='#39'Text'#39' defaultToken='#39'string'#39'>'
          '    <Regex token0='#39'escaped'#39' priority='#39'10'#39' regex='#39'\\\\'#39' />'
          '    <Regex token0='#39'escaped'#39' regex='#39'\\[a-z &quot; ]'#39' />    '
          '    <Regex token0='#39'escaped'#39' regex='#39'\\0x[a-fA-F0-9]+'#39' />'
          '  </Scheme>'
          ''
          
            '  <Scheme name='#39'BadString'#39' inherit='#39'String'#39' defaultToken='#39'badStr' +
            'ing'#39'>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'StringFind'#39'>'
          '    <Regex token0='#39'badString'#39'> '
          '        &apos; ( [^\\] | \\[a-z &apos;] | \\0x[a-fA-F0-9]+ )?'
          '    </Regex>'
          ''
          '    <Regex token0='#39'string'#39' priority='#39'10'#39'> '
          
            '        &apos; ( [^\\] | \\[a-z &apos;] | \\0x[a-fA-F0-9]+ ) &ap' +
            'os;'
          '    </Regex>'
          ''
          '    <Regex innerScheme='#39'BadString'#39' > '
          '        &quot; (.*?\\ &quot; )*? .* $ '
          '    </Regex>'
          ''
          '    <Regex innerScheme='#39'String'#39' priority='#39'10'#39'> '
          '        &quot; (.*?\\ &quot; )*? &quot;'
          '    </Regex>'
          ''
          '    <Regex innerScheme='#39'String'#39' priority='#39'20'#39'> '
          '        &quot; (.*?\\ &quot; )*? .*? [^\\] &quot;'
          '    </Regex>  '
          ''
          '    <Regex innerScheme='#39'String'#39' priority='#39'30'#39'> '
          '        &quot; &quot;'
          '    </Regex>'
          ''
          '  </Scheme>'
          '  '
          
            '  <Scheme name='#39'Preprocessor'#39' defaultToken='#39'preprocessor'#39' inheri' +
            't='#39'BaseSyntax'#39' >'
          ''
          '    <IdentRe>\b[a-zA-Z]+\b</IdentRe>'
          ''
          '    <Keywords>'
          '      if ifdef endif else using include define undef pragma'
          '    </Keywords>'
          ''
          '  </Scheme>'
          ''
          '  <Scheme name='#39'BadPreprocessor'#39' defaultToken='#39'badPreprocessor'#39'>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'BaseSyntax'#39' inherit='#39'Numbers'#39'>'
          '    <Regex innerScheme='#39'Comment'#39' regex='#39'//.*$'#39' />'
          ''
          ''
          '    <RegexBlock start='#39'\/\*'#39' end='#39'\*\/'#39' end_token0='#39'comment'#39' '
          '                innerScheme='#39'Comment'#39'/>'
          ''
          
            '    <Regex token0='#39'symbol'#39' regex='#39'[   \}   \{    \]    \[  \( \)' +
            ' &gt; &lt; ]'#39' />'
          '    <Regex token0='#39'symbol'#39' regex='#39'[-:?\~=+!^;,]'#39' />'
          ''
          ''
          '  </Scheme>'
          ''
          
            '  <Scheme name='#39'Main'#39' inherit='#39'BaseSyntax'#39' inherit0='#39'StringFind'#39 +
            ' '
          '          defaultToken='#39'default'#39'           '
          ''
          '          keywordsIgnoreCase='#39'false'#39
          '  >'
          '    <KeywordRegex>\b[a-zA-Z_][\w_]*\b</KeywordRegex>'
          ''
          '    <Keywords>'
          '      asm auto bool break case char const continue'
          '      default do double else enum export'
          '      extern false float for goto if inline int long '
          '      register return short signed sizeof static '
          
            '      switch typedef union unsigned void volatile wchar_t while ' +
            'NULL'
          '      __try __finally __catch'
          '    </Keywords>'
          ''
          ''
          
            '    <Regex innerScheme='#39'Preprocessor'#39' innerContentGroup='#39'1'#39' prio' +
            'rity='#39'10'#39' >'
          '        ^ \s* \# ([a-zA-Z]+) .* $'
          '    </Regex>'
          ''
          '    <Regex innerScheme='#39'BadPreprocessor'#39' innerContentGroup='#39'1'#39'>'
          '        ^ .*? \S .*? \# ([a-zA-Z]+) .* $'
          '    </Regex>'
          ''
          '    <RegexBlock innerScheme='#39'Preprocessor'#39' '
          '                innerContentGroup='#39'1'#39
          '                priority='#39'100'#39'>'
          '        <Start> ^ \s* \#([a-zA-Z]+) .* \\ \s* $  </Start>'
          '        <End>   (^ .* [^ \\ \s ] \s* $) | (^ \s* $)  </End>'
          '    </RegexBlock>'
          ''
          '    '
          '    <SkipSyntaxToken token='#39'comment'#39' />'
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start> '
          '            [ preprocessor:if  preprocessor:ifdef  ]'
          '        </Start>'
          ''
          '        <End> [ preprocessor:ifend  preprocessor:endif ] </End>'
          '    </SyntaxBlock>'
          ''
          ''
          '        '
          '    <SyntaxBlock capture="true">'
          '        <Start> id  sym:(  [^ sym:;    sym:}   sym:{   ]*  '
          
            '                sym:) ( sym::   [^ sym:;    sym:}   sym:{   ]+  ' +
            ' )? sym:{'
          '        </Start>'
          ''
          '        <End> sym:\}  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true" priority='#39'10'#39'>'
          '        <Start>                 '
          
            '            [ kw:while  kw:do kw:if  kw:else  kw:__try  kw:__fin' +
            'ally   kw:switch ]'
          '                                '
          '            [^ sym:;  sym:}  ]*?    sym:\{'
          '        </Start>'
          ''
          '        <End> sym:}  </End>'
          '    </SyntaxBlock>'
          '        '
          ''
          
            '    <SyntaxBlock capture="true" priority='#39'100'#39'  startGroupUsed='#39 +
            '1'#39'>'
          '        <Start>'
          
            '                    (  [ kw:while  kw:if  ]  sym:(   [^  sym:;  ' +
            ' sym:}    sym:{   ]+ sym:)   )    '
          ''
          '                    [^ sym:{  sym:}  sym:; ]+ sym:;'
          ''
          '             '
          '        </Start>'
          ''
          '        <End> sym:;  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="false" priority='#39'0'#39'  >'
          '        <Start> sym:{  </Start>'
          '        <End> sym:}  </End>'
          '    </SyntaxBlock>'
          ''
          '  </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'CPP'
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
          '        </Regex>                '
          '  </Scheme>'
          ''
          '  <Scheme name='#39'Numbers'#39'>'
          
            '    <Regex token0='#39'number'#39'>\b (0x \d+ [lL]? | \d+ (e \d*)? [lLdD' +
            'fF]? ) \b</Regex>'
          
            '    <Regex token0='#39'number'#39'>\b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? ' +
            '\d+) \b</Regex>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'Comment'#39' inherit='#39'Text'#39' defaultToken='#39'comment'#39'>'
          
            '    <Regex token0='#39'st'#39' regex='#39' \/\* | \*\/   '#39' />               ' +
            ' '
          '            '
          '     <SyntaxBlock capture="true">'
          '        <Start> st:/*  </Start>'
          '        <End> st:*/  </End>'
          '     </SyntaxBlock>                '
          '  </Scheme>'
          ''
          '  <Scheme name='#39'String'#39' inherit='#39'Text'#39' defaultToken='#39'string'#39'>'
          '    <Regex token0='#39'escaped'#39' priority='#39'10'#39' regex='#39'\\\\'#39' />  '
          '    <Regex token0='#39'escaped'#39' regex='#39'\\[a-z &quot; ]'#39' />    '
          '    <Regex token0='#39'escaped'#39' regex='#39'\\0x[a-fA-F0-9]+'#39' />'
          '  </Scheme>'
          ''
          
            '  <Scheme name='#39'BadString'#39' inherit='#39'String'#39' defaultToken='#39'badStr' +
            'ing'#39'>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'StringFind'#39'>'
          '    <Regex token0='#39'badString'#39'> '
          '        &apos; ( [^\\] | \\[a-z &apos;] | \\0x[a-fA-F0-9]+ )?'
          '    </Regex>'
          ''
          '    <Regex token0='#39'string'#39' priority='#39'10'#39'> '
          
            '        &apos; ( [^\\] | \\[a-z &apos;] | \\0x[a-fA-F0-9]+ ) &ap' +
            'os;'
          '    </Regex>'
          ''
          '    <Regex innerScheme='#39'BadString'#39' > '
          '        &quot; (.*?\\ &quot; )*? .* $ '
          '    </Regex>'
          ''
          '    <Regex innerScheme='#39'String'#39' priority='#39'10'#39'> '
          '        &quot; (.*?\\ &quot; )*? &quot;'
          '    </Regex>'
          ''
          '    <Regex innerScheme='#39'String'#39' priority='#39'20'#39'> '
          '        &quot; (.*?\\ &quot; )*? .*? [^\\] &quot;'
          '    </Regex>  '
          ''
          '    <Regex innerScheme='#39'String'#39' priority='#39'30'#39'> '
          '        &quot; &quot;'
          '    </Regex>'
          '    '
          '  </Scheme>'
          '  '
          
            '  <Scheme name='#39'Preprocessor'#39' defaultToken='#39'preprocessor'#39' inheri' +
            't='#39'BaseSyntax'#39' >'
          ''
          '    <IdentRe>\b[a-zA-Z]+\b</IdentRe>'
          ''
          '    <Keywords>'
          '      if ifdef endif else using include define undef pragma'
          '    </Keywords>'
          ''
          '  </Scheme>'
          ''
          '  <Scheme name='#39'BadPreprocessor'#39' defaultToken='#39'badPreprocessor'#39'>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'BaseSyntax'#39' inherit='#39'Numbers'#39'>'
          '    <Regex innerScheme='#39'Comment'#39' regex='#39'//.*$'#39' />'
          ''
          ''
          '    <RegexBlock start='#39'\/\*'#39' end='#39'\*\/'#39' end_token0='#39'comment'#39' '
          '                innerScheme='#39'Comment'#39'/>'
          ''
          
            '    <Regex token0='#39'symbol'#39' regex='#39'[   \}   \{    \]    \[  \( \)' +
            ' &gt; &lt; ]'#39' />'
          '    <Regex token0='#39'symbol'#39' regex='#39'[-:?\~=+!^;,]'#39' />'
          ''
          ''
          '  </Scheme>'
          ''
          '  <Scheme name='#39'Main'#39' inherit='#39'BaseSyntax'#39' '
          '          inherit1='#39'StringFind'#39' '
          '          defaultToken='#39'default'#39'           '
          ''
          '          keywordsIgnoreCase='#39'false'#39
          '  >'
          '    <KeywordRegex>\b[a-zA-Z_][\w_]*\b</KeywordRegex>'
          ''
          '    <Keywords>'
          
            '      asm auto bool break case catch char class const const_cast' +
            ' continue'
          
            '      default delete do double dynamic_cast else enum explicit e' +
            'xport'
          
            '      extern false float for friend goto if inline int long muta' +
            'ble'
          '      namespace new operator private protected public register'
          
            '      reinterpret_cast return short signed sizeof static static_' +
            'cast struct'
          
            '      switch template this throw true try typedef typeid typenam' +
            'e union'
          
            '      unsigned using virtual void volatile wchar_t while nullptr' +
            '  NULL'
          '      __try __finally'
          '    </Keywords>'
          ''
          ''
          
            '    <Regex innerScheme='#39'Preprocessor'#39' innerContentGroup='#39'1'#39' prio' +
            'rity='#39'10'#39' >'
          '        ^ \s* \# ([a-zA-Z]+) .* $'
          '    </Regex>'
          ''
          '    <Regex innerScheme='#39'BadPreprocessor'#39' innerContentGroup='#39'1'#39'>'
          '        ^ .*? \S .*? \# ([a-zA-Z]+) .* $'
          '    </Regex>'
          ''
          '    <RegexBlock innerScheme='#39'Preprocessor'#39' '
          '                innerContentGroup='#39'1'#39
          '                priority='#39'100'#39'>'
          '        <Start> ^ \s* \#([a-zA-Z]+) .* \\ \s* $  </Start>'
          '        <End>   (^ .* [^ \\ \s ] \s* $) | (^ \s* $)  </End>'
          '    </RegexBlock>'
          ''
          ''
          '    <SkipSyntaxToken token='#39'comment'#39' />'
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start> '
          '            [ preprocessor:if  preprocessor:ifdef  ]'
          '        </Start>'
          ''
          '        <End> [ preprocessor:ifend  preprocessor:endif ] </End>'
          '    </SyntaxBlock>'
          ''
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start> [ kw:class  kw:struct ]'
          '                [^ sym:; ]+ sym:\{ '
          '        </Start>'
          ''
          '        <End> sym:} </End>'
          '    </SyntaxBlock>'
          ''
          '        '
          '    <SyntaxBlock capture="true">'
          '        <Start> id  '
          '                sym:(  '
          '                    [^ sym:;    sym:}   sym:{   ]*  '
          '                sym:) '
          '                ( '
          '                    sym:: '
          '                    [^ sym:;    sym:}   sym:{   ]+   '
          '                )? '
          '                sym:{'
          '        </Start>'
          ''
          '        <End> sym:\}  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true" priority='#39'10'#39'>'
          '        <Start>                 '
          
            '            [ kw:while  kw:do kw:if  kw:else  kw:namespace  kw:t' +
            'ry kw:catch  kw:__try  kw:__finally   kw:switch ]'
          '                                '
          '            [^ sym:;  sym:}  ]*?    sym:\{'
          '        </Start>'
          ''
          '        <End> sym:}  </End>'
          '    </SyntaxBlock>'
          '        '
          ''
          
            '    <SyntaxBlock capture="true" priority='#39'100'#39'  startGroupUsed='#39 +
            '1'#39'>'
          '        <Start>'
          
            '                    (  [ kw:while  kw:if  ]  sym:(   [^  sym:;  ' +
            ' sym:}    sym:{   ]+ sym:)   )    '
          ''
          '                    [^ sym:{  sym:}  sym:; ]+ sym:;'
          ''
          '             '
          '        </Start>'
          ''
          '        <End> sym:;  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="false" priority='#39'0'#39'  >'
          '        <Start> sym:{  </Start>'
          '        <End> sym:}  </End>'
          '    </SyntaxBlock>'
          ''
          '  </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'CSS'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ' '
          '<SchemeList root='#39'Main'#39'>'
          ''
          ''
          '  <Scheme name='#39'Comment'#39' defaultToken='#39'comment'#39'>'
          '      <SyntaxBlock capture="true">'
          '        <Start> commentOpen </Start>'
          '        <End> commentClose </End>'
          '      </SyntaxBlock>      '
          '  </Scheme>'
          '  '
          '  <Scheme name='#39'CssInProp'#39' defaultToken='#39'cssAttrListBG'#39'>'
          '  '
          
            '      <!-- Searches for url attributes like: url('#39'www.url.com'#39') ' +
            '-->  '
          '      '
          '      <Regex token1='#39'cssUrlAttr'#39
          '             token2='#39'cssUrlAttr'#39
          '             token3='#39'cssUrlAttr'#39'             '
          '             token4='#39'cssUrlHref'#39
          '             token5='#39'cssUrlAttr'#39
          '             token6='#39'cssUrlAttr'#39
          '             token7='#39'cssUrlAttr'#39
          '             priority='#39'100'#39
          '      >'
          '          ( url  \(   \s*  )'
          '          ( [ &quot; &apos; ]+ )'
          '          ( \s* )'
          '          (.+?)'
          '          ( \2 )'
          '          ( \s* )          '
          '          ( \s*  \)  )'
          '      </Regex>'
          ''
          '      <Regex token1='#39'cssUrlAttr'#39
          '             token2='#39'cssUrlHref'#39
          '             token3='#39'cssUrlAttr'#39
          '             priority='#39'100'#39
          '      >'
          '          ( url  \(   \s*  )'
          '          ([^ &quot; &apos; ]+?)'
          '          ( \s*  \)  )'
          '      </Regex>'
          '            '
          '      <!-- Simple attribute value -->'
          '      <Regex token0='#39'attributeValue'#39'>'
          '          [^ \s , ]'
          '      </Regex>'
          '            '
          '      <!-- String attribute value -->'
          '      <Regex token0='#39'attributeValue'#39' priority='#39'10'#39'>'
          '          ([&quot; &apos;]) .*? \1 '
          '      </Regex>'
          ''
          '      <!-- Unfinished string -->  '
          '      <Regex token0='#39'badAttributeValue'#39' priority='#39'5'#39' >'
          '          [&quot; &apos;] .+ '
          '      </Regex>  '
          ''
          '      <!-- Unfinished url -->  '
          '      <Regex token0='#39'badAttributeValue'#39
          '             priority='#39'50'#39' >'
          '          url \( [^ ) ]+ \)?'
          '      </Regex>  '
          '      '
          '  </Scheme>'
          '  '
          '  <Scheme name='#39'CssProps'#39' >'
          ''
          '      <SyntaxBlock capture="true">'
          '        <Start> tagOpen </Start>'
          '        <End> tagClose </End>'
          '      </SyntaxBlock>'
          ''
          '      <RegexBlock innerScheme='#39'CssInProp'#39
          '                  start_token0='#39'attributeName'#39
          '                  end_token0='#39'tagClose'#39' >'
          '        <Start> (\b[ \w - ]+:) </Start>        '
          '        <End> (?= \} ) | ; | $ </End>        '
          '      </RegexBlock>'
          '            '
          '  </Scheme>'
          '  '
          '  <Scheme name='#39'Main'#39' >'
          '        <Regex token0='#39'cssRule'#39'>\w+</Regex>        '
          '        '
          
            '        <Regex token0='#39'cssRelSymbol'#39'>[* &gt; . &lt; #]+</Regex> ' +
            '       '
          ''
          
            '        <RegexBlock innerScheme='#39'CssProps'#39' start_token0='#39'tagOpen' +
            #39' end_token0='#39'tagClose'#39' >'
          '            <Start> \{ </Start>        '
          '            <End> \} </End>    '
          '        </RegexBlock>'
          ''
          '        <RegexBlock innerScheme='#39'Comment'#39
          '                    start_token0='#39'commentOpen'#39'    '
          '                    end_token0='#39'commentClose'#39' '
          '                    priority='#39'1000'#39' >'
          '          <Start> &lt; !--  </Start>           '
          '          <End> --&gt; </End>        '
          '        </RegexBlock>'
          ''
          '        <RegexBlock innerScheme='#39'Comment'#39
          '                    start_token0='#39'commentOpen'#39'    '
          '                    end_token0='#39'commentClose'#39'>'
          '          <Start> \/\*  </Start>           '
          '          <End> \*\/ </End>        '
          '        </RegexBlock>        '
          '        '
          '        '
          '        <RegexBlock innerScheme='#39'CssInProp'#39
          '                    start_token0='#39'attributeName'#39
          '                    end_token0='#39'tagClose'#39' >'
          '          <Start> ^ \s* @import </Start>        '
          '          <End> ; | $ </End>        '
          '        </RegexBlock>'
          '                '
          '  </Scheme>'
          '    '
          '</SchemeList>')
      end
      item
        Name = 'DFM'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          ''
          '    <Scheme name='#39'Numbers'#39'>'
          '        <Regex token0='#39'number'#39'>'
          '            \b (0x \d+ [lL]? | \d+ (e \d*)? [lLdDfF]? ) \b'
          '        </Regex>'
          '        '
          '        <Regex token0='#39'number'#39'>'
          '            \b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? \d+) \b'
          '        </Regex>'
          '    </Scheme>'
          ''
          '    <Scheme name='#39'String'#39' defaultToken='#39'string'#39'>'
          '    </Scheme>'
          ''
          '    <Scheme name='#39'Binary'#39' defaultToken='#39'comment'#39'>        '
          '        <SyntaxBlock capture="true">'
          '            <Start> commentStart  </Start>'
          '            <End> commentEnd  </End>'
          '        </SyntaxBlock>        '
          '    </Scheme>'
          ''
          '    <Scheme name='#39'Main'#39' inherit='#39'Numbers'#39' '
          '            defaultToken='#39'default'#39'           '
          ''
          '            keywordsIgnoreCase='#39'true'#39
          '    >'
          '        <KeywordRegex>\b[a-zA-Z_]\w*\b</KeywordRegex>'
          ''
          '        <Keywords>    '
          '            object  end item'
          '        </Keywords>'
          ''
          '        <RegexBlock innerScheme='#39'String'#39' start_token0='#39'string'#39' '
          '                    end_token0='#39'string'#39' >'
          ''
          '            <Start> &apos;  </Start>        '
          '            <End> &apos; </End>        '
          '        </RegexBlock>'
          ''
          
            '        <RegexBlock innerScheme='#39'Binary'#39' start_token0='#39'commentSt' +
            'art'#39' '
          '                    end_token0='#39'commentEnd'#39' >'
          '            <Start> \{  </Start>        '
          '            <End> \} </End>        '
          '        </RegexBlock>'
          ''
          
            '        <Regex token0='#39'symbol'#39' regex='#39'[   \]  \#  \[  \( \) &gt;' +
            ' &lt; ]'#39' />'
          '        <Regex token0='#39'symbol'#39' regex='#39'[-:?\~=+!^;,]'#39' />'
          '        '
          '        <SyntaxBlock capture="true">'
          '            <Start> [ kw:item kw:object ] </Start>'
          '            <End> kw:end  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> sym:&lt;  </Start>'
          '            <End> sym:&gt;  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> sym:(  </Start>'
          '            <End> sym:)  </End>'
          '        </SyntaxBlock>'
          ''
          '    </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'HTML'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ' '
          '<SchemeList root='#39'Main'#39'>'
          ''
          '  <Scheme name='#39'EmbedLang'#39' >'
          
            '    <RegexBlock innerScheme='#39'Tag'#39' start_token0='#39'tagOpen'#39' end_tok' +
            'en0='#39'tagClose'#39' >'
          '        <Start> &lt; [\w:]+ </Start>        '
          '        <End> (?= /? &gt;) </End>        '
          '    </RegexBlock>'
          '    '
          '  </Scheme>'
          '  '
          '  <Scheme name='#39'Comment'#39' defaultToken='#39'comment'#39'>'
          '  </Scheme>'
          ''
          '    '
          '  <Scheme name='#39'Css'#39' inherit='#39'EmbedLang'#39' '
          '          defaultToken='#39'defaultEmbed'#39'  >'
          ''
          
            '    <RegexBlock innerScheme='#39'CSS.Main'#39' start_token0='#39'tagOpen'#39' en' +
            'd_token0='#39'tagClose'#39' >'
          '        <Start> &gt; </Start>        '
          '        <End> (?= &lt; / \s* style ) </End>        '
          '    </RegexBlock>    '
          '          '
          '  </Scheme>'
          '  '
          '  <Scheme name='#39'JavaScript'#39' inherit='#39'EmbedLang'#39
          '          defaultToken='#39'defaultEmbed'#39'>'
          ''
          '   '
          
            '    <RegexBlock innerScheme='#39'JavaScript.Main'#39' start_token0='#39'tagO' +
            'pen'#39' end_token0='#39'tagClose'#39' >'
          '        <Start> &gt; </Start>        '
          '        <End> (?= &lt; / \s* script ) </End>        '
          '    </RegexBlock> '
          ''
          '  </Scheme>'
          ''
          '  <Scheme name='#39'VBScript'#39' '
          '          allIgnoreCase='#39'true'#39
          '          inherit='#39'EmbedLang'#39
          '          defaultToken='#39'defaultEmbed'#39'>'
          ''
          
            '    <RegexBlock innerScheme='#39'VB.Main'#39' start_token0='#39'tagOpen'#39' end' +
            '_token0='#39'tagClose'#39' >'
          '        <Start> &gt; </Start>        '
          '        <End> (?= &lt; / \s* script ) </End>        '
          '    </RegexBlock>    '
          ''
          '  </Scheme>'
          ''
          '  <Scheme name='#39'PHPInScript'#39' '
          '          inherit='#39'EmbedLang'#39
          '          defaultToken='#39'defaultEmbed'#39'>'
          ''
          
            '    <RegexBlock innerScheme='#39'PHP.Language'#39' start_token0='#39'tagOpen' +
            #39' end_token0='#39'tagClose'#39' >'
          '        <Start> &gt; </Start>        '
          '        <End> (?= &lt; / \s* script ) </End>        '
          '    </RegexBlock>    '
          ''
          '  </Scheme>'
          ''
          '  <Scheme name='#39'PHP'#39' inherit0='#39'PHP.Language'#39' '
          '          defaultToken='#39'defaultEmbed'#39'>          '
          '  </Scheme>'
          ''
          
            '  <Scheme name='#39'DTD'#39' allIgnoreCase='#39'true'#39' defaultToken='#39'comment'#39 +
            '>  '
          '  '
          '    <KeywordRegex>\b\w+\b</KeywordRegex>'
          '    '
          '    <Keywords>HTML PUBLIC</Keywords>'
          '    '
          '    <Regex token0="fpi">'
          '        (&quot;|&apos;)'
          '        \s* '
          '        -//W3C//DTD '
          '        \s+ HTML '
          '        \s+ \d\.\d+(\s+\w+)?//EN '
          '        \s* '
          '        \1'
          '    </Regex>'
          '                                        '
          '    <Regex token0="url">'
          '        (&quot;|&apos;)'
          '        \s* '
          '           \w+://\w+(\.\w+)+((/\w+/)+\S*)?'
          '        \s* '
          '        \1        '
          '    </Regex>'
          '      '
          '  </Scheme>'
          ''
          '  <Scheme name='#39'AttrStringQuot'#39'>'
          '    <Regex token0='#39'attributeValue'#39'> [^ &quot; ]+</Regex>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'AttrStringApos'#39'>'
          '    <Regex token0='#39'attributeValue'#39'> [^ &apos; ]+</Regex>'
          '  </Scheme>'
          ''
          '    '
          '  <Scheme name='#39'AttributeValue'#39' defaultToken='#39'attributeValue'#39' />'
          '  '
          '  <Scheme name='#39'Tag'#39'>  '
          '  '
          '    <Regex token0='#39'attributeName'#39' priority='#39'10'#39'>'
          '        \b[\w\-]+ \s* = \s*        '
          '        '
          '    </Regex>'
          ''
          '    <Regex token0='#39'attributeValue'#39'>'
          '        [^ &lt; &gt; &quot; &apos; = \s ]+         '
          '    </Regex>'
          ''
          
            '    <RegexBlock innerScheme='#39'AttrStringQuot'#39' start_token0='#39'attri' +
            'buteValue'#39' '
          '        end_token0='#39'attributeValue'#39' >'
          ''
          '        <Start> &quot;  </Start>        '
          '        <End> &quot; </End>        '
          '    </RegexBlock>'
          ''
          
            '    <RegexBlock innerScheme='#39'AttrStringApos'#39' start_token0='#39'attri' +
            'buteValue'#39' '
          '        end_token0='#39'attributeValue'#39' >'
          ''
          '        <Start> &apos;  </Start>        '
          '        <End> &apos; </End>        '
          '    </RegexBlock>'
          ''
          '  </Scheme>'
          '  '
          ''
          '  <Scheme name='#39'Main'#39' defaultToken='#39'htmlText'#39
          '          keywordsIgnoreCase='#39'true'#39' '
          '          allIgnoreCase='#39'true'#39'>'
          '    '
          '    <Regex token0='#39'entity'#39'>'
          '        &amp;[a-zA-Z]+;'
          '    </Regex>'
          '                    '
          '    <RegexBlock innerScheme='#39'Comment'#39' end_token0='#39'comment'#39' >'
          '        <Start> &lt; !--  </Start>        '
          '        <End> --&gt; </End>        '
          '    </RegexBlock>'
          ''
          
            '    <RegexBlock innerScheme='#39'DTD'#39' start_token0='#39'dtdTagStartEnd'#39' ' +
            'end_token0='#39'dtdTagStartEnd'#39' >'
          '        <Start> &lt; !DOCTYPE  </Start>        '
          '        <End> &gt; </End>        '
          '    </RegexBlock>'
          ''
          '    <RegexBlock innerScheme='#39'JavaScript'#39' '
          #9#9'end_token0='#39'tagClose'#39
          '                closeInnerSchemes='#39'true'#39#9#9
          #9#9'>'
          '        <Start>         '
          '          &lt; script '
          '          '
          '            '
          '           ('
          '            \s+'
          
            '            (language \s* = \s* (&quot;|&apos;) \s* (javascript|' +
            'JScript|ECMAScript) \s* \3 ) |'
          
            '            (type \s* = \s* (&quot;|&apos;) \s* text/(javascript' +
            '|JScript|ECMAScript) \s* \6 )'
          '           )?'
          '          '
          '          .*?'
          '          &gt;'
          '        </Start>        '
          
            '        <End> ( / &gt;) | (&lt; / \s* script \s* &gt;)  </End>  ' +
            '      '
          '    </RegexBlock>'
          ''
          '    <RegexBlock innerScheme='#39'VBScript'#39' '
          '                end_token0='#39'tagClose'#39' priority='#39'10'#39
          '                closeInnerSchemes='#39'true'#39'                '
          '                >'
          '        <Start>         '
          '          &lt; script '
          '          '
          '            \s+                             '
          '           ( '
          
            '            (language \s* = \s* (&quot;|&apos;) \s* VBScript \s*' +
            ' \3 ) |'
          
            '            (type \s* = \s* (&quot;|&apos;) \s* text/VBScript \s' +
            '* \6 )'
          '           ) '
          '          '
          '          .*?'
          '          &gt;'
          '        </Start>        '
          '        <End> ( / &gt;) | (&lt; / \s* script \s* &gt;)  </End>'
          '    </RegexBlock>'
          ''
          '    <RegexBlock innerScheme='#39'PHPInScript'#39' '
          '                end_token0='#39'tagClose'#39' '
          '                priority='#39'200'#39
          '                closeInnerSchemes='#39'true'#39'                '
          '                >'
          '        <Start> '
          '          &lt; script '
          '          '
          '            \s+                             '
          '           ( '
          
            '            (language \s* = \s* (&quot;|&apos;) \s* php \s* \3 )' +
            ' |'
          
            '            (type \s* = \s* (&quot;|&apos;) \s* text/php \s* \5 ' +
            ')'
          '           ) '
          '          '
          '          .*?'
          '          &gt;'
          '        </Start>        '
          '        <End> ( / &gt;) | (&lt; / \s* script \s* &gt;)  </End>'
          '    </RegexBlock>'
          ''
          '    <RegexBlock innerScheme='#39'PHP'#39' '
          '                start_token0='#39'tagOpen'#39' '
          '                end_token0='#39'tagClose'#39' '
          '                priority='#39'100'#39
          '                closeInnerSchemes='#39'true'#39
          '                >'
          '        <Start> '
          '          &lt; \?php '
          '        </Start>        '
          '        <End> \? &gt; </End>        '
          '    </RegexBlock>'
          ''
          
            '    <RegexBlock innerScheme='#39'Css'#39' end_token0='#39'tagClose'#39' priority' +
            '='#39'100'#39' >'
          '        <Start> '
          '          &lt; style (\s+ [^ &lt; &gt; ]*)?'
          '          &gt;'
          '        </Start>        '
          '        <End> ( / &gt;) | (&lt; / \s* style \s* &gt;)  </End>'
          '    </RegexBlock>'
          ''
          
            '    <RegexBlock innerScheme='#39'Tag'#39' start_token0='#39'tagOpen'#39' end_tok' +
            'en0='#39'tagClose'#39' >'
          '        <Start> &lt; [\w:]+ </Start>        '
          '        <End> /? &gt; </End>        '
          '    </RegexBlock>'
          ''
          '    <Regex token0='#39'tagClose'#39' >'
          '        &lt; /  [\w:]+ &gt; '
          '    </Regex>           '
          '  </Scheme>'
          '</SchemeList>'
          '')
      end
      item
        Name = 'JavaScript'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '      <Scheme name='#39'Text'#39' inherit='#39'Numbers'#39'>'
          '            <Regex token0='#39'email'#39'>'
          '                [_a-zA-Z\d\-\.]{1,40}'
          '                @ '
          '                ([_ a-z A-Z \d \-]+ '
          '                (\. [_ a-z A-Z \d \-]+ )+ )'
          '            </Regex>                '
          '      </Scheme>'
          ''
          '      <Scheme name='#39'Numbers'#39'>'
          
            '        <Regex token0='#39'number'#39'>\b (0x \d+ [lL]? | \d+ (e \d*)? [' +
            'lLdDfF]? ) \b</Regex>'
          
            '        <Regex token0='#39'number'#39'>\b [+\-]? \d+ (\. \d+)? ([eE] [+\' +
            '-]? \d+) \b</Regex>'
          '      </Scheme>'
          ''
          
            '      <Scheme name='#39'Comment'#39' inherit='#39'Text'#39' defaultToken='#39'commen' +
            't'#39'>'
          
            '        <Regex token0='#39'st'#39' regex='#39' \/\* | \*\/   '#39' />           ' +
            '     '
          '                '
          '         <SyntaxBlock capture="true">'
          '            <Start> st:/*  </Start>'
          '            <End> st:*/  </End>'
          '         </SyntaxBlock>                '
          '      </Scheme>'
          ''
          
            '      <Scheme name='#39'String'#39' inherit='#39'Text'#39' defaultToken='#39'string'#39 +
            '>'
          
            '        <Regex token0='#39'escaped'#39' priority='#39'10'#39' regex='#39'\\\\'#39' />   ' +
            '   '
          '        <Regex token0='#39'escaped'#39' regex='#39'\\[a-z &quot; ]'#39' />    '
          '        <Regex token0='#39'escaped'#39' regex='#39'\\0x[a-fA-F0-9]+'#39' />'
          '      </Scheme>'
          ''
          
            '      <Scheme name='#39'BadString'#39' inherit='#39'String'#39' defaultToken='#39'ba' +
            'dString'#39'>'
          '      </Scheme>'
          ''
          '      <Scheme name='#39'StringFind'#39'>'
          '        <Regex innerScheme='#39'BadString'#39' > '
          '            (&quot;|&apos;) (.*?\\ \1 )*? .* $ '
          '        </Regex>'
          ''
          '        <Regex innerScheme='#39'String'#39' priority='#39'10'#39'> '
          '            (&quot;|&apos;) (.*?\\ \1 )*? \1'
          '        </Regex>'
          ''
          '        <Regex innerScheme='#39'String'#39' priority='#39'20'#39'> '
          '            (&quot;|&apos;) (.*?\\ \1 )*? .*? [^\\] \1'
          '        </Regex>  '
          ''
          '        <Regex innerScheme='#39'String'#39' priority='#39'30'#39'> '
          '            (&quot;|&apos;) \1'
          '        </Regex>'
          '        '
          '      </Scheme>'
          ''
          '    <Scheme name='#39'RegexFind'#39' defaultToken='#39'defaultEmbed'#39'>'
          '        <Regex token0='#39'escaped'#39' regex='#39'\\/'#39' />            '
          '    </Scheme>'
          '    '
          
            '    <Scheme name='#39'RegexSubst'#39' inherit='#39'RegexFind'#39' defaultToken='#39 +
            'defaultEmbed'#39'>'
          '        <Regex token0='#39'escaped'#39' regex='#39'\$\d'#39' />                '
          '    </Scheme>'
          ''
          '    <Scheme name='#39'DefaultEmpty'#39' defaultToken='#39'default'#39' />'
          '    '
          '    <Scheme name='#39'Main'#39' inherit='#39'StringFind'#39' '
          '            defaultToken='#39'default'#39'           '
          ''
          '            keywordsIgnoreCase='#39'false'#39
          '    >'
          '    <KeywordRegex>\b[a-zA-Z_][\w_]*\b</KeywordRegex>'
          ''
          '    <Keywords>'
          '            Boolean'
          '            Array'
          '            join length reverse sort'
          '            NaN '
          '            null '
          '            true false '
          '            Infinity '
          '            undefined '
          '            Break '#9#9'continue '#9#9#9'for  in  if else return  while '
          '            '
          '            function new this var with  arguments '
          '            '
          '            Global escape unescape eval Number '
          '            Object new instanceof  delete typeof void '#9#9#9
          '            throw  try catch finally with'
          '    </Keywords>'
          ''
          ''
          '    <Regex innerScheme='#39'Comment'#39' regex='#39'//.*$'#39' />'
          ''
          ''
          '    <RegexBlock start='#39'\/\*'#39' end='#39'\*\/'#39' end_token0='#39'comment'#39' '
          '                innerScheme='#39'Comment'#39'/>'
          ''
          
            '    <Regex token0='#39'symbol'#39' regex='#39'[   \}   \{    \]    \[  \( \)' +
            ' &gt; &lt; ]'#39' />'
          '    <Regex token0='#39'symbol'#39' regex='#39'[-:?\~=+!^;,]'#39' />'
          ''
          '    <RegexBlock innerScheme='#39'DefaultEmpty'#39' '
          '                start_token0='#39'symbol'#39
          '                end_token0='#39'symbol'#39' '
          '                priority='#39'100'#39
          '                chainBlock='#39'RegexFindEnd'#39
          '    >'
          ''
          '        <Start> \s* ([ =( ]) \s* (?= / )  </Start>        '
          '        <End> (?= / )  </End>        '
          '    </RegexBlock>'
          '    '
          '    <ChainBlock name='#39'RegexFindEnd'#39' '
          '                innerScheme='#39'RegexFind'#39' '
          '                end_token0='#39'regexEnd'#39' '
          '                chainBlock='#39'RegexFindEnd2'#39
          '    >'
          '        <End> / </End>        '
          '    </ChainBlock>'
          ''
          '    <ChainBlock name='#39'RegexFindEnd2'#39' '
          '                innerScheme='#39'RegexFind'#39' '
          '                end_token0='#39'regexEnd'#39' '
          '    >'
          '        <End> /[igmx]* </End>        '
          '    </ChainBlock>'
          '        '
          '    <ChainBlock name='#39'RegexSubstEnd'#39' '
          '                end_token0='#39'regexEnd'#39' '
          '                innerScheme='#39'RegexSubst'#39'  >'
          '        <End> /[igmx]* </End>        '
          '    </ChainBlock>'
          '    '
          '    <RegexBlock innerScheme='#39'RegexFind'#39' '
          '                start_token0='#39'regexStart'#39' '
          '                end_token0='#39'regexEnd'#39' '
          '                chainBlock='#39'RegexSubstEnd'#39'>'
          ''
          '        <Start> s/  </Start>        '
          '        <End> /[igmx]* </End>        '
          '    </RegexBlock>'
          ''
          ''
          '    <SkipSyntaxToken token='#39'comment'#39' />'
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start> kw:function  id  '
          '                sym:(  '
          '                        [^ sym:;    sym:}   sym:{   ]*  '
          '                sym:) '
          '                sym:{'
          '        </Start>'
          ''
          '        <End> sym:\}  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true" priority='#39'10'#39'>'
          '        <Start>                 '
          
            '            [ kw:while  kw:do kw:if  kw:else  kw:try kw:catch  k' +
            'w:finally  kw:switch ]'
          '                                '
          '            [^ sym:;  sym:}  ]*?    sym:\{'
          '        </Start>'
          ''
          '        <End> sym:}  </End>'
          '    </SyntaxBlock>'
          '        '
          ''
          
            '    <SyntaxBlock capture="true" priority='#39'100'#39'  startGroupUsed='#39 +
            '1'#39'>'
          '        <Start>'
          
            '                    (  [ kw:while  kw:if  kw:with ]  sym:(   [^ ' +
            ' sym:;   sym:}    sym:{   ]+ sym:)   )    '
          ''
          '                    [^ sym:{  sym:}  sym:; ]+ sym:;'
          ''
          '            '
          '        </Start>'
          ''
          '        <End> sym:;  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="false" priority='#39'0'#39'  >'
          '        <Start> sym:{  </Start>'
          '        <End> sym:}  </End>'
          '    </SyntaxBlock>'
          ''
          '    </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'Lua'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '    <Scheme name='#39'Text'#39' inherit='#39'Numbers'#39'>                '
          '    '
          '        <Regex token0='#39'email'#39'>'
          '            [_a-zA-Z\d\-\.]{1,40}'
          '            @ '
          '            ([_ a-z A-Z \d \-]+ '
          '            (\. [_ a-z A-Z \d \-]+ )+ )'
          '        </Regex>'
          '    </Scheme>'
          ''
          '    <Scheme name='#39'Numbers'#39'>'
          '        <Regex token0='#39'number'#39'>'
          '            \b (0x \d+ [lL]? | \d+ (e \d*)? [lLdDfF]? ) \b'
          '        </Regex>'
          '        '
          '        <Regex token0='#39'number'#39'>'
          '            \b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? \d+) \b'
          '        </Regex>'
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'Comment'#39' inherit='#39'Text'#39' defaultToken='#39'comment'#39 +
            '  />'
          ''
          '    <Scheme name='#39'String'#39' inherit='#39'Text'#39' defaultToken='#39'string'#39'>'
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'StringInterpolation'#39' inherit='#39'String'#39' defaultT' +
            'oken='#39'string'#39'>'
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\[a-z 0 &quot; &apos; ]'#39 +
            ' />'
          '        <Regex token0='#39'escaped'#39' regex='#39'\\ \d{1,3}'#39' />'
          '    </Scheme>'
          ''
          '    <Scheme name='#39'Main'#39' inherit='#39'Numbers'#39' '
          '            defaultToken='#39'default'#39'           '
          ''
          '            keywordsIgnoreCase='#39'true'#39
          '    >'
          '        <KeywordRegex>\b[a-zA-Z_]\w*\b</KeywordRegex>'
          ''
          '        <Keywords>    '
          '             and       break     do        else      elseif'
          '             end       false     for       function  if'
          '             in        local     nil       not       or'
          
            '             repeat    return    then      true      until     w' +
            'hile            '
          '        </Keywords>'
          ''
          
            '        <RegexBlock innerScheme='#39'StringInterpolation'#39' start_toke' +
            'n0='#39'string'#39' '
          '                    end_token0='#39'string'#39' >'
          ''
          '            <Start> &quot; | &apos;  </Start>        '
          '            <End> $0 </End>        '
          '        </RegexBlock>'
          ''
          
            '        <RegexBlock innerScheme='#39'String'#39' start_token0='#39'string'#39' p' +
            'riority='#39'100'#39
          '                    end_token0='#39'string'#39' >'
          ''
          '            <Start> \[ (\=*) \[  </Start>        '
          '            <End> \] $1 \] </End>        '
          '        </RegexBlock>'
          ''
          ''
          
            '        <RegexBlock innerScheme='#39'Comment'#39' start_token0='#39'comment'#39 +
            ' priority='#39'100'#39
          '                    end_token0='#39'comment'#39' >'
          ''
          '            <Start> --\[ (\=*) \[  </Start>        '
          '            <End> \] $1 \] </End>        '
          '        </RegexBlock>'
          ''
          
            '        <Regex innerScheme='#39'Comment'#39' priority='#39'1000'#39' regex='#39'--([' +
            '^ \[ ].*)?$'#39' />'
          '        '
          
            '        <RegexBlock start='#39'\/\*'#39' end='#39'\*\/'#39' end_token0='#39'comment'#39 +
            ' '
          '                innerScheme='#39'Comment'#39'/>'
          ''
          
            '        <Regex token0='#39'symbol'#39' regex='#39'[   \}   \{    \]  \#  \[ ' +
            ' \( \) &gt; &lt; ]'#39' />'
          '        <Regex token0='#39'symbol'#39' regex='#39'[-:?\~=+!^;,]'#39' />'
          ''
          '        <SkipSyntaxToken token='#39'comment'#39' />'
          ''
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> ( kw:local )? kw:function  </Start>'
          '            <End> kw:end  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> kw:if </Start>'
          '            <End> kw:end  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> kw:repeat </Start>'
          '            <End> kw:until  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> [ kw:while kw:for ] .+? kw:do  </Start>'
          '            <End> kw:end  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> kw:do  </Start>'
          '            <End> kw:end  </End>'
          '        </SyntaxBlock>'
          '    </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'Pascal'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '      <Scheme name='#39'Text'#39' inherit='#39'Numbers'#39'>'
          '            <Regex token0='#39'email'#39'>'
          '                [_a-zA-Z\d\-\.]{1,40}'
          '                @ '
          '                ([_ a-z A-Z \d \-]+ '
          '                (\. [_ a-z A-Z \d \-]+ )+ )'
          '            </Regex>                '
          '      </Scheme>'
          ''
          '      <Scheme name='#39'Numbers'#39'>'
          
            '        <Regex token0='#39'number'#39'>\b (0x \d+ [lL]? | \d+ (e \d*)? [' +
            'lLdDfF]? ) \b</Regex>'
          
            '        <Regex token0='#39'number'#39'>\b [+\-]? \d+ (\. \d+)? ([eE] [+\' +
            '-]? \d+) \b</Regex>'
          '      </Scheme>'
          ''
          
            '      <Scheme name='#39'Comment'#39' inherit='#39'Text'#39' defaultToken='#39'commen' +
            't'#39'>'
          '        <Regex token0='#39'st'#39' regex='#39' [ {} ]   '#39' />'
          '        <Regex token0='#39'st'#39' regex='#39' ( \(\* )|( \*\) )   '#39' />'
          '                '
          '         <SyntaxBlock capture="true">'
          '            <Start> st:{  </Start>'
          '            <End> st:}  </End>'
          '         </SyntaxBlock>                '
          '         '
          '         <SyntaxBlock capture="true">'
          '            <Start> st:(*  </Start>'
          '            <End> st:*)  </End>'
          '         </SyntaxBlock>                         '
          '      </Scheme>'
          ''
          
            '      <Scheme name='#39'String'#39' inherit='#39'Text'#39' defaultToken='#39'string'#39 +
            '>'
          '      </Scheme>'
          ''
          
            '      <Scheme name='#39'BadString'#39' inherit='#39'String'#39' defaultToken='#39'ba' +
            'dString'#39'>'
          '      </Scheme>'
          ''
          '      <Scheme name='#39'StringFind'#39'>'
          '        <Regex innerScheme='#39'BadString'#39' > '
          '            &apos; (.*?\\ &apos; )*? .* $ '
          '        </Regex>'
          ''
          '        <Regex innerScheme='#39'String'#39' priority='#39'10'#39'> '
          '            &apos; (.*?\\ &apos; )*? &apos; '
          '        </Regex>'
          ''
          '        <Regex innerScheme='#39'String'#39' priority='#39'20'#39'> '
          '            &apos; (.*?\\ &apos; )*? .*? [^\\] &apos;'
          '        </Regex>  '
          ''
          '        <Regex innerScheme='#39'String'#39' priority='#39'30'#39'> '
          '            &apos;  &apos; '
          '        </Regex>'
          '        '
          '      </Scheme>'
          '    '
          
            '      <Scheme name='#39'Preprocessor'#39' defaultToken='#39'preprocessor'#39' in' +
            'herit='#39'Numbers'#39' >'
          ''
          '        <IdentRe>\b[a-zA-Z]+\b</IdentRe>'
          ''
          '        <Keywords>'
          '          if ifdef endif else ifend defined'
          '        </Keywords>'
          ''
          
            '        <Regex token0='#39'symbol'#39' regex='#39'[   \}   \{    \]    \[  \' +
            '( \) &gt; &lt; ]'#39' />'
          '        <Regex token0='#39'symbol'#39' regex='#39'[-=+]'#39' />'
          ''
          '      </Scheme>'
          '    '
          '    <Scheme name='#39'Main'#39' inherit='#39'StringFind'#39' '
          '            defaultToken='#39'default'#39'           '
          ''
          '            keywordsIgnoreCase='#39'false'#39
          '    >'
          '    <KeywordRegex>\b[a-zA-Z_][\w_]*\b</KeywordRegex>'
          ''
          '    <Keywords>'
          
            '        and     else    inherited   packed  then    array   end ' +
            '    initialization      procedure '
          
            '        threadvar       as          except  inline  program to  ' +
            '    asm                 exports '
          
            '        interface       property    try     begin   file    is  ' +
            '    raise               type '
          
            '        case            final       label   record  unit    clas' +
            's   finalization        library '
          
            '        repeat          unsafe      const   finally mod     reso' +
            'urcestring              until '
          
            '        constructor     for         nil     sealed  uses    dest' +
            'ructor                  function '
          
            '        not             set         var     dispinterface   goto' +
            '    object              shl '
          
            '        while           div         if      of      shr     with' +
            '    do                  implementation '
          
            '        or              static      xor     downto  in      out ' +
            '    string '
          ''
          
            '        absolute        dynamic     local   platform        requ' +
            'ires                    abstract '
          
            '        export          message     private                 resi' +
            'dent                    assembler '
          
            '        external        name        protected               safe' +
            'call                    automated '
          
            '        far             near        public  stdcall         cdec' +
            'l                       forward '
          
            '        nodefault       published   stored  contains        impl' +
            'ements                  overload '
          
            '        read            varargs     default index   override    ' +
            '                        readonly '
          
            '        virtual         deprecated  inline  package register    ' +
            '    write   dispid      library '
          '        pascal          reintroduce writeonly '
          '    </Keywords>'
          ''
          ''
          '    <Regex innerScheme='#39'Comment'#39' regex='#39'//.*$'#39' />'
          ''
          ''
          
            '    <RegexBlock start='#39'\(\*'#39' end='#39'\*\)'#39' end_token0='#39'comment'#39' pri' +
            'ority='#39'10'#39
          '                innerScheme='#39'Comment'#39'/>'
          ''
          
            '    <RegexBlock start='#39'\{\$'#39' end='#39'\}'#39' start_token0='#39'preprocessor' +
            #39' end_token0='#39'preprocessor'#39' priority='#39'100'#39
          '                innerScheme='#39'Preprocessor'#39'/>'
          ''
          
            '    <RegexBlock start='#39'\{'#39' end='#39'\}'#39' end_token0='#39'comment'#39' priorit' +
            'y='#39'100'#39
          '                innerScheme='#39'Comment'#39'/>'
          ''
          
            '    <Regex token0='#39'symbol'#39' regex='#39'[   \}   \{    \]    \[  \( \)' +
            ' &gt; &lt; ]'#39' />'
          '    <Regex token0='#39'symbol'#39' regex='#39'[-:?\~=+!^;,]'#39' />'
          ''
          ''
          '    <SkipSyntaxToken token='#39'comment'#39' />'
          ''
          '    <SyntaxBlock capture="true">'
          
            '        <Start> [ kw:procedure kw:function kw:destructor  kw:con' +
            'structor ] '
          '                [^ kw:procedure kw:initialization '
          '                   kw:finalization'
          '                   kw:implementation'
          '                   kw:destructor  '
          '                   kw:constructor'
          '                   kw:class'
          '                   kw:end ]+? kw:begin  </Start>'
          '        <End> kw:end  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true" priority='#39'100'#39' >'
          
            '        <Start> kw:if [^ kw:end sym:; ]+? kw:then  kw:begin </St' +
            'art>'
          '        <End> kw:end  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true">'
          
            '        <Start> [ kw:if kw:for kw:while kw:with kw:else  ]  [^ k' +
            'w:begin kw:end  sym:; ]+ </Start>'
          '        <End> sym:;  </End>'
          '    </SyntaxBlock>'
          ''
          ''
          '    <SyntaxBlock capture="true">'
          
            '        <Start> [ kw:with kw:for kw:while ] [^ kw:end  sym:; ]+?' +
            ' kw:do  kw:begin </Start>'
          '        <End> kw:end  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true">'
          
            '        <Start> id sym:= [ kw:class kw:record ]  [^ sym:; kw:of ' +
            ' ]</Start>'
          '        <End> kw:end  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="false" priority='#39'0'#39'  >'
          '        <Start> kw:begin  </Start>'
          '        <End> kw:end  </End>'
          '    </SyntaxBlock>'
          ''
          '    </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'Perl'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '    <Scheme name='#39'Text'#39' inherit='#39'Numbers'#39'>                '
          '    '
          '        <Regex token0='#39'email'#39'>'
          '            [_a-zA-Z\d\-\.]{1,40}'
          '            @ '
          '            ([_ a-z A-Z \d \-]+ '
          '            (\. [_ a-z A-Z \d \-]+ )+ )'
          '        </Regex>'
          '    '
          
            '        <Regex token0='#39'st'#39' regex='#39' \/\* | \*\/   '#39' />           ' +
            '     '
          '                '
          '        <SyntaxBlock capture="true">'
          '            <Start> st:/*  </Start>'
          '            <End> st:*/  </End>'
          '        </SyntaxBlock>              '
          '    </Scheme>'
          ''
          '    <Scheme name='#39'Numbers'#39'>'
          '        <Regex token0='#39'number'#39'>'
          '            \b (0x \d+ [lL]? | \d+ (e \d*)? [lLdDfF]? ) \b'
          '        </Regex>'
          '        '
          '        <Regex token0='#39'number'#39'>'
          '            \b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? \d+) \b'
          '        </Regex>'
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'Comment'#39' inherit='#39'Text'#39' defaultToken='#39'comment'#39 +
            '  />'
          ''
          '    <Scheme name='#39'StringInterpolation'#39'>'
          '        <Regex token0='#39'escaped'#39' regex='#39'\\[a-z &quot; ]'#39' />'
          '        <Regex token0='#39'escaped'#39' regex='#39'\\0\d+'#39' />        '
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\x[0-9A-Fa-f]+'#39' />      ' +
            '          '
          '        <Regex token0='#39'escaped'#39' regex='#39'[$%]\w+'#39' />    '
          '    </Scheme>'
          '    '
          
            '    <Scheme name='#39'String'#39' inherit='#39'StringInterpolation'#39' inherit0' +
            '='#39'Text'#39' '
          '            defaultToken='#39'string'#39'>'
          '                        '
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'HereDoc'#39' inherit0='#39'Text'#39' defaultToken='#39'string'#39 +
            '>'
          '        <SyntaxBlock capture="true">'
          '            <Start> blockStart  </Start>'
          '            <End> blockEnd  </End>'
          '        </SyntaxBlock>    '
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'RegexFind'#39' inherit='#39'StringInterpolation'#39' defau' +
            'ltToken='#39'defaultEmbed'#39'>'
          '        <Regex token0='#39'escaped'#39' regex='#39'\\/'#39' />            '
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'RegexSubst'#39' inherit='#39'RegexFind'#39' defaultToken='#39 +
            'defaultEmbed'#39'>'
          '        <Regex token0='#39'escaped'#39' regex='#39'\$\d'#39' />                '
          '    </Scheme>'
          ''
          '    <Scheme name='#39'PerlDoc'#39' defaultToken='#39'docDefault'#39'>'
          ''
          
            '        <Regex lineBound='#39'true'#39' token0='#39'docBlockStart'#39' > =begin ' +
            ' </Regex>'
          
            '        <Regex lineBound='#39'true'#39' token0='#39'docBlockEnd'#39' > =end  </R' +
            'egex>'
          
            '        <Regex lineBound='#39'true'#39' token0='#39'docInstruction'#39' > =[a-zA' +
            '-Z_]\w+  </Regex>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> docStart  </Start>'
          '            <End> docEnd  </End>'
          '        </SyntaxBlock>    '
          '        '
          '        <SyntaxBlock capture="true">'
          '            <Start> docBlockStart  </Start>'
          '            <End> docBlockEnd  </End>'
          '        </SyntaxBlock>    '
          '        '
          '    </Scheme>'
          '    '
          ''
          '    <Scheme name='#39'ShellCommand'#39' defaultToken='#39'defaultEmbed'#39'>'
          '        <SyntaxBlock capture="true">'
          '            <Start> blockStart  </Start>'
          '            <End> blockEnd  </End>'
          '        </SyntaxBlock>    '
          '    </Scheme>'
          '                    '
          ''
          '    <Scheme name='#39'DefaultEmpty'#39' defaultToken='#39'default'#39' />'
          '            '
          '    <Scheme name='#39'BaseSyntax'#39' inherit='#39'Numbers'#39'>'
          '        <Regex innersScheme='#39'Comment'#39' regex='#39'//.*$'#39' />'
          ''
          '        <Regex innerScheme='#39'Comment'#39' regex='#39'\#.*$'#39' />'
          ''
          
            '        <RegexBlock start='#39'\/\*'#39' end='#39'\*\/'#39' end_token0='#39'comment'#39 +
            ' '
          '                innerScheme='#39'Comment'#39'/>'
          ''
          
            '        <Regex token0='#39'symbol'#39' regex='#39'[   \}   \{    \]    \[  \' +
            '( \) &gt; &lt; ]'#39' />'
          '        <Regex token0='#39'symbol'#39' regex='#39'[-:?\~=+!^;,]'#39' />'
          ''
          '        <Regex regex='#39'\$[a-z_A-Z0-9#]+'#39' />'
          ''
          '        <Regex regex='#39'&lt; [^ &gt; ]+ &gt;'#39' token0='#39'keyword'#39'/>'
          '    '
          '        <RegexBlock innerScheme='#39'DefaultEmpty'#39' '
          '                start_token0='#39'symbol'#39
          '                end_token0='#39'symbol'#39' '
          '                priority='#39'100'#39
          '                chainBlock='#39'RegexFindEnd'#39
          '        >'
          ''
          '            <Start> \s* ([ =( ]) \s* (?= / )  </Start>        '
          '            <End> (?= / )  </End>        '
          '        </RegexBlock>'
          ''
          '        <ChainBlock name='#39'RegexFindEnd'#39' '
          '                innerScheme='#39'RegexFind'#39' '
          '                end_token0='#39'regexEnd'#39' '
          '                chainBlock='#39'RegexFindEnd2'#39
          '        >'
          '            <End> / </End>        '
          '        </ChainBlock>'
          ''
          '        <ChainBlock name='#39'RegexFindEnd2'#39' '
          '                innerScheme='#39'RegexFind'#39' '
          '                end_token0='#39'regexEnd'#39' '
          '        >'
          '            <End> /[cgimosx]* </End>        '
          '        </ChainBlock>'
          ''
          '                '
          '        <RegexBlock innerScheme='#39'RegexFind'#39' '
          '                    start_token0='#39'regexStart'#39' '
          '                    end_token0='#39'regexEnd'#39' >'
          ''
          '            <Start> m/  </Start>        '
          '            <End> /[cgimosx]* </End>        '
          '        </RegexBlock>'
          ''
          '        <RegexBlock innerScheme='#39'RegexFind'#39' '
          '                    start_token0='#39'regexStart'#39' '
          '                    end_token0='#39'regexEnd'#39' >'
          ''
          '            <Start> q(q?|[xw])/  </Start>        '
          '            <End> / </End>        '
          '        </RegexBlock>'
          ''
          '        <RegexBlock innerScheme='#39'RegexFind'#39' '
          '                    start_token0='#39'regexStart'#39' '
          '                    end_token0='#39'regexEnd'#39' >'
          ''
          '            <Start> qr/  </Start>        '
          '            <End> /[imosx]* </End>        '
          '        </RegexBlock>'
          ''
          '        <RegexBlock innerScheme='#39'RegexFind'#39' '
          '                    start_token0='#39'regexStart'#39' '
          '                    end_token0='#39'regexEnd'#39' >'
          ''
          '            <Start> \?  </Start>        '
          '            <End> \? </End>        '
          '        </RegexBlock>'
          ''
          '        <ChainBlock name='#39'RegexSubstEnd'#39' '
          '                    end_token0='#39'regexEnd'#39' '
          '                    innerScheme='#39'RegexSubst'#39'  >'
          '            <End> /[egimosx]* </End>        '
          '        </ChainBlock>'
          ''
          '        <ChainBlock name='#39'RegexSubstEnd2'#39' '
          '                    end_token0='#39'regexEnd'#39' '
          '                    innerScheme='#39'RegexSubst'#39'  >'
          '            <End> /[cds]* </End>        '
          '        </ChainBlock>'
          ''
          '        <RegexBlock innerScheme='#39'RegexFind'#39' '
          '                    start_token0='#39'regexStart'#39' '
          '                    end_token0='#39'regexEnd'#39' '
          '                    chainBlock='#39'RegexSubstEnd'#39'>'
          ''
          '            <Start> s/  </Start>        '
          '            <End> / </End>        '
          '        </RegexBlock>'
          ''
          '        <RegexBlock innerScheme='#39'RegexFind'#39' '
          '                    start_token0='#39'regexStart'#39' '
          '                    end_token0='#39'regexEnd'#39' '
          '                    chainBlock='#39'RegexSubstEnd2'#39'>'
          ''
          '            <Start> (tr|y)/  </Start>        '
          '            <End> / </End>        '
          '        </RegexBlock>'
          ''
          ''
          '        <RegexBlock innerScheme='#39'PerlDoc'#39' '
          '                    priority='#39'100'#39
          '                    lineBound='#39'true'#39
          '                    start_token0='#39'docStart'#39' '
          '                    end_token0='#39'docEnd'#39'>'
          ''
          '            <Start> =[a-zA-Z_]\w+  </Start>        '
          '            <End> =cut </End>        '
          '        </RegexBlock>'
          ''
          '    </Scheme>'
          '    '
          '    <Scheme name='#39'Main'#39' inherit='#39'BaseSyntax'#39' '
          '            defaultToken='#39'default'#39'           '
          ''
          '            keywordsIgnoreCase='#39'false'#39
          '    >'
          '        <KeywordRegex>\b[a-z()A-Z_][\w_]*\b</KeywordRegex>'
          ''
          '        <Keywords>    '
          '            __FILE__    __LINE__    __PACKAGE__'
          '            __END__     __DATA__'
          '            continue else elsif for foreach if last '
          '            next redo sub unless until while        '
          '            accept alarm atan2 bind binmode bless caller chdir'
          '            chmod abs chomp chop chown chr chroot closedir close'
          
            '            connect cos crypt dbmclose dbmopen defined delete di' +
            'e do'
          
            '            dump each endgrent endhostent endnetent endprotoent ' +
            'endpwent'
          
            '            endservent eof eval exec exists exit exp fcntl filen' +
            'o flock'
          '            fork format formline getc getgrent getgrgid getgrnam'
          
            '            gethostbyaddr gethostbyname gethostent getlogin getn' +
            'etbyaddr'
          
            '            getnetbyname getnetent getpeername getpgrp getpriori' +
            'ty'
          '            getprotobyname getprotobynumber getprotoent getpwent'
          
            '            getpwnam getpwuid getservbyname getservbyport getser' +
            'vent'
          
            '            getsockname getsockopt glob gmtime goto grep hex ind' +
            'ex'
          
            '            int ioctl join keys kill last lcfirst lc length link' +
            ' listen'
          
            '            local localtime log lstat map mkdir msgctl msgget ms' +
            'grcv'
          
            '            msgsnd my next no oct open opendir ord pack package ' +
            'pipe'
          '            pop pos printf print prototype push qq quotemeta qw'
          
            '            qx q rand readdir readline readlink readpipe read re' +
            'cv'
          
            '            redo ref rename require reset return reverse rewindd' +
            'ir'
          
            '            rindex rmdir scalar seek seekdir select semctl semge' +
            't'
          
            '            semop send setgrent sethostent setnetent setpgrp set' +
            'priority'
          
            '            setprotoent setpwent setservent setsockopt shift shm' +
            'ctl shmget'
          
            '            shmread shmwrite shutdown sin sleep socket socketpai' +
            'r sort splice'
          
            '            split sprintf sqrt srand stat study substr sub symli' +
            'nk syscall'
          
            '            sysopen sysread sysseek system syswrite s tell telld' +
            'ir tie tied'
          
            '            time times truncate tr ucfirst uc umask undef unlink' +
            ' unpack'
          
            '            unshift untie use utime values vec waitpid wait want' +
            'array'
          '            warn write            '
          '        </Keywords>'
          ''
          
            '        <RegexBlock innerScheme='#39'HereDoc'#39' start_token0='#39'blockSta' +
            'rt'#39' '
          '                    priority='#39'100'#39
          '                    end_token0='#39'blockEnd'#39' >'
          ''
          
            '            <Start>  [^ &lt; ]? &lt; &lt; (\w+) ; </Start>      ' +
            '  '
          '            <End> $1 </End>        '
          '        </RegexBlock>'
          ''
          
            '        <RegexBlock innerScheme='#39'ShellCommand'#39' start_token0='#39'blo' +
            'ckStart'#39' '
          '                    priority='#39'100'#39
          '                    end_token0='#39'blockEnd'#39' >'
          ''
          
            '            <Start>  [^ &lt; ]? &lt; &lt; \s? \`  (\w+) \` </Sta' +
            'rt>        '
          '            <End> $1 </End>        '
          '        </RegexBlock>'
          ''
          '        <RegexBlock innerScheme='#39'String'#39' start_token0='#39'string'#39' '
          '                    end_token0='#39'string'#39' >'
          ''
          '            <Start> &quot;  </Start>        '
          '            <End> &quot; </End>        '
          '        </RegexBlock>'
          ''
          '        <RegexBlock innerScheme='#39'ShellCommand'#39
          '                    start_token0='#39'defaultEmbed'#39
          '                    end_token0='#39'defaultEmbed'#39' >'
          ''
          '            <Start> &apos;  </Start>        '
          '            <End> &apos; </End>        '
          '        </RegexBlock>'
          ''
          '        <SkipSyntaxToken token='#39'comment'#39' />'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> kw:sub  id  '
          '                    '
          '                    sym:{'
          '            </Start>'
          ''
          '            <End> sym:\}  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> [ kw:do ] sym:{'
          '            </Start>'
          ''
          '            <End> sym:\}   </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> [ kw:else kw:continue ] sym:{'
          '            </Start>'
          ''
          '            <End> sym:\}  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true" priority='#39'10'#39'>'
          '            <Start>                 '
          
            '                ( id sym:: )? [ kw:while  kw:if  kw:switch kw:fo' +
            'r ]'
          '                                    '
          '                sym:( .+  sym:)   sym:\{'
          '            </Start>'
          ''
          '            <End> sym:}  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true" priority='#39'10'#39'>'
          '            <Start>                 '
          '                id sym::   sym:\{'
          '            </Start>'
          ''
          '            <End> sym:}  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> '
          '                kw:foreach  id  sym:( .+  sym:)  sym:{'
          '            </Start>'
          ''
          '            <End> sym:\}  </End>'
          '        </SyntaxBlock>'
          ''
          ''
          '        <SyntaxBlock capture="false" priority='#39'0'#39'  >'
          '            <Start> sym:{  </Start>'
          '            <End> sym:}  </End>'
          '        </SyntaxBlock>'
          ''
          '    </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'PHP'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '    <Scheme name='#39'Text'#39' inherit='#39'Numbers'#39'>                '
          '    '
          '        <Regex token0='#39'email'#39'>'
          '            [_a-zA-Z\d\-\.]{1,40}'
          '            @ '
          '            ([_ a-z A-Z \d \-]+ '
          '            (\. [_ a-z A-Z \d \-]+ )+ )'
          '        </Regex>'
          '    '
          
            '        <Regex token0='#39'st'#39' regex='#39' \/\* | \*\/   '#39' />           ' +
            '     '
          '                '
          '        <SyntaxBlock capture="true">'
          '            <Start> st:/*  </Start>'
          '            <End> st:*/  </End>'
          '        </SyntaxBlock>              '
          '    </Scheme>'
          ''
          '    <Scheme name='#39'Numbers'#39'>'
          '        <Regex token0='#39'number'#39'>'
          '            \b (0x \d+ [lL]? | \d+ (e \d*)? [lLdDfF]? ) \b'
          '        </Regex>'
          '        '
          '        <Regex token0='#39'number'#39'>'
          '            \b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? \d+) \b'
          '        </Regex>'
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'Comment'#39' inherit='#39'Text'#39' defaultToken='#39'comment'#39 +
            '  />'
          ''
          '    <Scheme name='#39'String'#39' inherit='#39'Text'#39' defaultToken='#39'string'#39'>'
          
            '        <Regex token0='#39'escaped'#39' priority='#39'10'#39' regex='#39'\\\\'#39' />   ' +
            ' '
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\[a-z &quot; &apos; ]'#39' /' +
            '>'
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\x[a-fA-F0-9 ]{1,2}'#39' pri' +
            'ority='#39'10'#39'/>        '
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'StringInterpolation'#39' inherit='#39'String'#39' defaultT' +
            'oken='#39'string'#39'>'
          '        <Regex token0='#39'escaped'#39' regex='#39'\$ \w[ \w - &gt; ]*'#39' />'
          '    </Scheme>'
          ''
          ''
          '      <Scheme name='#39'StringFind'#39'>'
          ''
          
            '        <RegexBlock innerScheme='#39'StringInterpolation'#39' start_toke' +
            'n0='#39'string'#39
          '                   end_token0='#39'string'#39' >'
          ''
          '           <Start>  &quot;  </Start>        '
          '           <End>   &quot; </End>        '
          '        </RegexBlock>'
          ''
          '        <RegexBlock innerScheme='#39'String'#39' start_token0='#39'string'#39
          '                   end_token0='#39'string'#39' >'
          ''
          '           <Start>  &apos;  </Start>        '
          '           <End>   &apos; </End>        '
          '        </RegexBlock>'
          '        '
          '      </Scheme>'
          ''
          ''
          
            '    <Scheme name='#39'HereDoc'#39' inherit0='#39'StringInterpolation'#39' defaul' +
            'tToken='#39'string'#39'>'
          '        <SyntaxBlock capture="true">'
          '            <Start> blockStart  </Start>'
          '            <End> blockEnd  </End>'
          '        </SyntaxBlock>    '
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'Language'#39' inherit='#39'Numbers'#39' inherit0='#39'StringFi' +
            'nd'#39' '
          '            defaultToken='#39'default'#39'           '
          ''
          '            keywordsIgnoreCase='#39'false'#39
          '    >'
          '        <KeywordRegex>\b[a-z()A-Z_][\w_]*\b</KeywordRegex>'
          ''
          '        <Keywords>    '
          '            __LINE__            __FILE__ '
          '            __FUNCTION__        __CLASS__'
          '            __METHOD__'
          '            and     or  xor     exception '
          '            array   as  break   case'
          '            class   const       continue '
          '            declare default     die()       do  '
          '            echo    else        elseif      empty() '
          '            enddeclare          endfor      endforeach '
          '            endif   endswitch   endwhile    eval() '
          '            exit()  extends     for         foreach '
          
            '            function            global      if          include(' +
            ')           '
          '            include_once()      isset()     list()      '
          '            new     print()     require()   require_once()      '
          '            return()            static      switch '
          '            unset() use         var         while '
          '            final   php_user_filter         interface '
          '            implements          extends     public      '
          '            private protected   abstract    clone '
          '            try     catch       throw       cfunction '
          '            old_function '
          '            E_WARNING           E_ERROR                 E_PARSE'
          '            E_NOTICE            E_CORE_ERROR                '
          
            '            E_CORE_WARNING      E_COMPILE_ERROR         E_COMPIL' +
            'E_WARNING '
          
            '            E_USER_ERROR        E_USER_WARNING          E_USER_N' +
            'OTICE '
          '            E_STRICT            E_RECOVERABLE_ERROR     E_ALL '
          '        </Keywords>'
          ''
          '        <Regex innerScheme='#39'Comment'#39' regex='#39'//.*$'#39' />'
          '        '
          
            '        <RegexBlock start='#39'\/\*'#39' end='#39'\*\/'#39' end_token0='#39'comment'#39 +
            ' '
          '                innerScheme='#39'Comment'#39'/>'
          ''
          
            '        <Regex token0='#39'symbol'#39' regex='#39'[   \}   \{    \]    \[  \' +
            '( \) &gt; &lt; ]'#39' />'
          '        <Regex token0='#39'symbol'#39' regex='#39'[-:?\~=+!^;,]'#39' />'
          ''
          ''
          
            '        <RegexBlock innerScheme='#39'HereDoc'#39' start_token0='#39'blockSta' +
            'rt'#39' '
          '                    priority='#39'100'#39
          '                    end_token0='#39'blockEnd'#39' >'
          ''
          
            '            <Start>  [^ &lt; ]? &lt; &lt; &lt; (\w+)  </Start>  ' +
            '      '
          '            <End> ^ $1 ; </End>        '
          '        </RegexBlock>'
          ''
          '        <SkipSyntaxToken token='#39'comment'#39' />'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> kw:function  id  sym:(  '
          '                    [^ sym:;    sym:}   sym:{   ]*  '
          '                    sym:) ( sym::   '
          '                    [^ sym:;    sym:}   sym:{   ]+   '
          '                    )? sym:{'
          '            </Start>'
          ''
          '            <End> sym:\}  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true" priority='#39'10'#39'>'
          '            <Start>                 '
          
            '                [ kw:while  kw:do kw:if  kw:else  kw:try kw:catc' +
            'h  kw:finally  kw:switch ]'
          '                                    '
          '                [^ sym:;  sym:}  ]*?    sym:\{'
          '            </Start>'
          ''
          '            <End> sym:}  </End>'
          '        </SyntaxBlock>'
          '            '
          ''
          
            '        <SyntaxBlock capture="true" priority='#39'100'#39'  startGroupUs' +
            'ed='#39'1'#39'>'
          '            <Start>'
          
            '                        (  [ kw:while  kw:if  kw:with ]  sym:(  ' +
            ' [^  sym:;   sym:}    sym:{   ]+ sym:)   )    '
          ''
          '                        [^ sym:{  sym:}  sym:; ]+ sym:;'
          ''
          '                '
          '            </Start>'
          ''
          '            <End> sym:;  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> kw:else sym:{  </Start>'
          '            <End> sym:}  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="false" priority='#39'0'#39'  >'
          '            <Start> sym:{  </Start>'
          '            <End> sym:}  </End>'
          '        </SyntaxBlock>'
          ''
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'LanguageEmbed'#39' inherit='#39'Language'#39' defaultToken' +
            '='#39'defaultEmbed'#39'>'
          '    </Scheme>'
          ''
          '    <TokenAlias name='#39'htmlText'#39' baseToken='#39'default'#39'/>'
          ''
          
            '    <Scheme name='#39'Main'#39' defaultToken='#39'htmlText'#39' inherit='#39'HTML.Ma' +
            'in'#39'>'
          '    '
          '        <RegexBlock innerScheme='#39'LanguageEmbed'#39' '
          '                    start_token0='#39'tagOpen'#39' '
          '                    end_token0='#39'tagClose'#39'>'
          '            <Start> '
          '              &lt; \?(php)?'
          '            </Start>        '
          '            <End> \? &gt; </End>        '
          '        </RegexBlock>'
          ''
          '        <RegexBlock innerScheme='#39'LanguageEmbed'#39' '
          '                    start_token0='#39'tagOpen'#39' '
          '                    end_token0='#39'tagClose'#39' '
          '                    >'
          '            <Start> '
          '              &lt; %'
          '            </Start>        '
          '            <End> % &gt; </End>        '
          '        </RegexBlock>'
          ''
          '    </Scheme>'
          '</SchemeList>'
          ''
          '')
      end
      item
        Name = 'Python'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '    <Scheme name='#39'Text'#39' inherit='#39'Numbers'#39'>                '
          '    '
          '        <Regex token0='#39'email'#39'>'
          '            [_a-zA-Z\d\-\.]{1,40}'
          '            @ '
          '            ([_ a-z A-Z \d \-]+ '
          '            (\. [_ a-z A-Z \d \-]+ )+ )'
          '        </Regex>'
          '    </Scheme>'
          ''
          '    <Scheme name='#39'Numbers'#39'>'
          '        <Regex token0='#39'number'#39'>'
          '            \b (0x \d+ [lL]? | \d+ (e \d*)? [lLdDfF]? ) \b'
          '        </Regex>'
          '        '
          '        <!-- [jJ] are Python imaginary literals -->'
          '        <Regex token0='#39'number'#39'>'
          '            \b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? \d+)? [jJ]? \b'
          '        </Regex>'
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'Comment'#39' inherit='#39'Text'#39' defaultToken='#39'comment'#39 +
            '  />'
          ''
          '    <Scheme name='#39'String'#39' inherit='#39'Text'#39' defaultToken='#39'string'#39'>'
          '        <Regex token0='#39'escaped'#39' regex='#39'\\[a-zA-Z0-9 &quot; ]'#39' />'
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\N\{[a-zA-Z_]+\}'#39' priori' +
            'ty='#39'10'#39' />'
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\u[0-9a-fA-F]{4}'#39' priori' +
            'ty='#39'10'#39' />        '
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\U[0-9a-fA-F]{8}'#39' priori' +
            'ty='#39'10'#39' />                '
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\x[0-9a-fA-F]{2}'#39' priori' +
            'ty='#39'10'#39' />'
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\o[0-7]{2}'#39' priority='#39'10' +
            #39' />'
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'BadString'#39' inherit='#39'String'#39' defaultToken='#39'badS' +
            'tring'#39'>'
          '    </Scheme>'
          ''
          '    <Scheme name='#39'BaseSyntax'#39' inherit='#39'Numbers'#39'>'
          '        <Regex innerScheme='#39'Comment'#39' regex='#39'\#.*$'#39' />'
          '        '
          
            '        <Regex token0='#39'privateSymbol'#39' regex='#39'\b_\w+\b'#39' />       ' +
            ' '
          
            '        <Regex token0='#39'privateSymbol'#39' regex='#39'\b__\w+(__)?\b'#39' /> ' +
            '       '
          
            '        <Regex token0='#39'keyword'#39' priority='#39'10'#39' regex='#39'\b__\w+__\b' +
            #39' />        '
          ''
          
            '        <Regex token0='#39'symbol'#39' regex='#39'[   \}   \{    \]    \[  \' +
            '( \) &gt; &lt; ]'#39' />'
          '        <Regex token0='#39'symbol'#39' regex='#39'[-:?\~=+!^;,]'#39' />'
          ''
          ''
          '        <Regex innerScheme='#39'BadString'#39' > '
          '            (u|ur)? (&quot;|&apos;) (.*?\\ \2 )*? .* $ '
          '        </Regex>'
          ''
          '        <Regex innerScheme='#39'String'#39' priority='#39'10'#39'> '
          '            (u|ur)? (&quot;|&apos;) (.*?\\ \2 )*? \2 '
          '        </Regex>'
          ''
          '        <Regex innerScheme='#39'String'#39' priority='#39'20'#39'> '
          '            (u|ur)? (&quot;|&apos;) (.*?\\ \2 )*? .*? [^\\] \2 '
          '        </Regex>'
          '        '
          '        <Regex innerScheme='#39'String'#39' priority='#39'30'#39'> '
          '            (u|ur)? (&quot;|&apos;)  \2 '
          '        </Regex>'
          ''
          '        '
          '        <RegexBlock innerScheme='#39'String'#39' '
          '                    priority='#39'100'#39
          
            '                    start_token0='#39'string'#39'                       ' +
            '  '
          '                    end_token0='#39'string'#39' >'
          ''
          
            '            <Start> (u|ur)? ( &quot;{3} | &apos;{3} ) </Start>  ' +
            '      '
          '            <End> $2 </End>        '
          '        </RegexBlock>'
          ''
          '    </Scheme>'
          '    '
          '    <Scheme name='#39'Main'#39' inherit='#39'BaseSyntax'#39' '
          '            defaultToken='#39'default'#39'           '
          ''
          '            keywordsIgnoreCase='#39'false'#39
          '    >'
          '        <KeywordRegex>\b[a-zA-Z_][\w_]*\b</KeywordRegex>'
          ''
          '        <Keywords>    '
          '            and       del       from      not       while    '
          '            as        elif      global    or        with     '
          '            assert    else      if        pass      yield    '
          '            break     except    import    print              '
          '            class     exec      in        raise              '
          '            continue  finally   is        return             '
          '            def       for       lambda    try      '
          '        </Keywords>'
          ''
          '    </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'Rexx'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '    <Scheme name='#39'Text'#39' inherit='#39'Numbers'#39'>                '
          '    '
          '        <Regex token0='#39'email'#39'>'
          '            [_a-zA-Z\d\-\.]{1,40}'
          '            @ '
          '            ([_ a-z A-Z \d \-]+ '
          '            (\. [_ a-z A-Z \d \-]+ )+ )'
          '        </Regex>'
          '    '
          
            '        <Regex token0='#39'st'#39' regex='#39' \/\* | \*\/   '#39' />           ' +
            '                     '
          '    </Scheme>'
          ''
          '    <Scheme name='#39'Numbers'#39'>'
          '        <Regex token0='#39'number'#39'>'
          '            \b (0x \d+ [lL]? | \d+ (e \d*)? [lLdDfF]? ) \b'
          '        </Regex>'
          '        '
          '        <Regex token0='#39'number'#39'>'
          '            \b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? \d+) \b'
          '        </Regex>'
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'Comment'#39' inherit='#39'Text'#39' defaultToken='#39'comment'#39 +
            '  />'
          ''
          '    <Scheme name='#39'String'#39' inherit='#39'Text'#39' defaultToken='#39'string'#39'>'
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'BadString'#39' inherit='#39'String'#39' defaultToken='#39'badS' +
            'tring'#39'>'
          '    </Scheme>'
          ''
          '    <Scheme name='#39'StringFind'#39'>'
          '        <Regex innerScheme='#39'BadString'#39' > '
          '            &apos; .* $ '
          '        </Regex>'
          ''
          '        <Regex innerScheme='#39'String'#39' priority='#39'10'#39'> '
          '            &apos; .*? &apos;'
          '        </Regex>'
          '    </Scheme>'
          ''
          '    <Scheme name='#39'Main'#39' inherit='#39'Numbers'#39' inherit0='#39'StringFind'#39' '
          '            defaultToken='#39'default'#39'           '
          ''
          '            keywordsIgnoreCase='#39'true'#39
          '    >'
          '        <KeywordRegex>\b[a-zA-Z_]\w*\b</KeywordRegex>'
          ''
          '        <Keywords>    '
          '            do          end     select  RC      RESULT  SIGL'
          
            '            address     arg     call    drop    else    error   ' +
            'exit    expose'
          
            '            forever     if      interpret       iterate         ' +
            'leave   otherwise'
          
            '            parse       procedure       pull    push    queue   ' +
            'return  say'
          
            '            signal      source  syntax  then    to      until   ' +
            'upper   value'
          
            '            var         when    while   abbrev  abs     bitand  ' +
            'bitor   bitxor'
          
            '            center      centre  changestr       charin  charout ' +
            'chars   compare'
          
            '            condition   copies  countstr        datatype        ' +
            'date    delstr'
          
            '            delword     digits  errortext       form    format  ' +
            'fuzz    insert'
          
            '            lastpos     left    length          linein  lineout ' +
            'lines   max'
          
            '            min         max     overlay         pos     queued  ' +
            'random  reverse'
          
            '            right       sign    sourceline      space   stream  ' +
            'strip   substr'
          
            '            subword     symbol  time            translate       ' +
            'trunc   verify'
          
            '            word        wordindex               wordlength      ' +
            'wordpos'
          '            words       xrange'
          '        </Keywords>'
          ''
          
            '        <Regex innerScheme='#39'Comment'#39' priority='#39'1000'#39' regex='#39'--([' +
            '^ \[ ].*)?$'#39' />'
          '        '
          
            '        <RegexBlock start='#39'\/\*'#39' end='#39'\*\/'#39' end_token0='#39'comment'#39 +
            ' '
          '                innerScheme='#39'Comment'#39'/>'
          ''
          
            '        <Regex token0='#39'symbol'#39' regex='#39'[   \}   \{    \]  \#  \[ ' +
            ' \( \) &gt; &lt; ]'#39' />'
          '        <Regex token0='#39'symbol'#39' regex='#39'[-:?\~=+!^;,]'#39' />'
          ''
          '        <SkipSyntaxToken token='#39'comment'#39' />'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> kw:else kw:do </Start>'
          '            <End> kw:end  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> kw:select </Start>'
          '            <End> kw:end  </End>'
          '        </SyntaxBlock>'
          ''
          ''
          '        <SyntaxBlock capture="true">'
          
            '            <Start> kw:if [^ kw:return kw:then ]+? kw:then kw:do' +
            ' </Start>'
          '            <End> kw:end  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> kw:do  </Start>'
          '            <End> kw:end  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> kw:signal kw:value </Start>'
          '            <End> kw:return  </End>'
          '        </SyntaxBlock>'
          ''
          '    </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'SQL'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '  <Scheme name='#39'Numbers'#39'>'
          
            '    <Regex token0='#39'number'#39'>\b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? ' +
            '\d+)? \b</Regex>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'Comment'#39' defaultToken='#39'comment'#39'>'
          '      <SyntaxBlock capture="true">'
          '        <Start> commentOpen </Start>'
          '        <End> commentClose </End>'
          '      </SyntaxBlock>      '
          '  </Scheme>'
          ''
          '  <Scheme name='#39'String'#39' defaultToken='#39'string'#39'>'
          '  </Scheme>'
          ''
          
            '  <Scheme name='#39'BadString'#39' inherit='#39'String'#39' defaultToken='#39'badStr' +
            'ing'#39'>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'StringFind'#39'>'
          #9'<Regex innerScheme='#39'BadString'#39' > '
          #9#9'&apos; (.*?\\ &apos; )*? .* $ '
          #9'</Regex>'
          ''
          #9'<Regex innerScheme='#39'String'#39' priority='#39'10'#39'> '
          #9#9'&apos; (.*?\\ &apos; )*? &apos; '
          #9'</Regex>'
          ''
          #9'<Regex innerScheme='#39'String'#39' priority='#39'20'#39'> '
          #9#9'&apos; (.*?\\ &apos; )*? .*? [^\\] &apos;'
          #9'</Regex>  '
          ''
          #9'<Regex innerScheme='#39'String'#39' priority='#39'30'#39'> '
          #9#9'&apos;  &apos; '
          #9'</Regex>'
          '        '
          '  </Scheme>'
          ''
          
            '  <Scheme name='#39'Main'#39' keywordsIgnoreCase='#39'true'#39' inherit='#39'StringF' +
            'ind'#39' inherit0='#39'Numbers'#39'>'
          ''
          '    <KeywordRegex>\b[a-zA-Z_][\w_]*\b</KeywordRegex>'
          ''
          #9'<!-- Common SQL Syntax -->'
          '    <Keywords>'
          #9#9'add all alter and any as asc authorization backup'
          #9#9'begin between body break browse bulk by cascade'
          #9#9'case check checkpoint close clustered coalesce'
          #9#9'column commit committed compute confirm constraint'
          #9#9'contains containstable continue controlrow create'
          #9#9'cross current current_date current_time current_timestamp'
          #9#9'current_user cursor database dbcc deallocate declare'
          #9#9'default delete deny desc disk distinct distributed'
          #9#9'double drop dummy dynamic else encryption end errlvl'
          #9#9'errorexit escape except exec exit fast_forward file'
          #9#9'fillfactor floppy for foreign forward_only freetext'
          #9#9'freetexttable from full function goto grant group'
          #9#9'having holdlock identity identity_insert identitycol'
          #9#9'if in index insensitive insert instead intersect into is'
          #9#9'isolation join key keyset kill left level like lineno load'
          #9#9'mirrorexit national nocheck nonclustered not null nullif of'
          #9#9'off offsets on once only open opendatasource openquery'
          #9#9'openrowset optimistic option or order outer over package'
          #9#9'percent perm permanent pipe plan precision prepare primary'
          #9#9'print privileges proc procedure processexit public raiserror'
          #9#9'read read_only readtext reconfigure references repeatable'
          #9#9'replication restore restrict return returns revoke right'
          
            #9#9'rollback row rowcount rowguidecol rule save schema schemabindi' +
            'ng'
          #9#9'scroll_locks select serializable session_user set setuser'
          #9#9'shutdown some sql_variant static statistics system_user table'
          
            #9#9'tape temp temporary textsize then to top tran transaction trig' +
            'ger'
          #9#9'truncate tsequal type_warning uncommitted union unique update'
          #9#9'updatetext use values varying view waitfor when where while'
          #9#9'with work writetext xml replace REVERSE'#9
          #9#9'varchar collate integer numeric '
          #9#9'FLOOR RAND COUNT CAST'
          '    </Keywords>'
          ''
          #9'<!--MySQL-->'
          #9'<Keywords>'
          #9#9'AUTO_INCREMENT INT LIMIT '
          #9#9'PROCEDURE FUNCTION BEGIN END'
          #9#9'EXECUTE USING'
          #9#9'OUTFILE'
          #9#9'FIELDS TERMINATED'
          #9#9'LINES OPTIONALLY ENCLOSED'
          #9#9'SUM LOCK TABLES UNLOCK'
          '    </Keywords>'
          #9
          #9'<Regex token0='#39'symbol'#39'>'
          
            #9#9'[ ; = + - / * &amp; | ^ ( ) \[ \] , . : ! ~ &lt; &gt; % { } ? ' +
            '# @  ]'
          #9'</Regex>'
          #9
          #9'<RegexBlock innerScheme='#39'Comment'#39
          #9#9#9#9'start_token0='#39'commentOpen'#39'    '
          #9#9#9#9'end_token0='#39'commentClose'#39
          #9#9#9#9'priority='#39'10'#39'>'
          #9'  <Start> \/\*  </Start>           '
          #9'  <End> \*\/ </End>        '
          #9'</RegexBlock>        '
          ''
          #9'<Regex innerScheme='#39'Comment'#39' priority='#39'10'#39'> -- .* </Regex>'
          '  </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'TCL'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '    <Scheme name='#39'Text'#39' inherit='#39'Numbers'#39'>                '
          '    '
          '        <Regex token0='#39'email'#39'>'
          '            [_a-zA-Z\d\-\.]{1,40}'
          '            @ '
          '            ([_ a-z A-Z \d \-]+ '
          '            (\. [_ a-z A-Z \d \-]+ )+ )'
          '        </Regex>'
          '    '
          
            '        <Regex token0='#39'st'#39' regex='#39' \/\* | \*\/   '#39' />           ' +
            '     '
          '                '
          '        <SyntaxBlock capture="true">'
          '            <Start> st:/*  </Start>'
          '            <End> st:*/  </End>'
          '        </SyntaxBlock>              '
          '    </Scheme>'
          ''
          '    <Scheme name='#39'Numbers'#39'>'
          '        <Regex token0='#39'number'#39'>'
          '            \b (0x \d+ [lL]? | \d+ (e \d*)? [lLdDfF]? ) \b'
          '        </Regex>'
          '        '
          '        <Regex token0='#39'number'#39'>'
          '            \b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? \d+) \b'
          '        </Regex>'
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'Comment'#39' inherit='#39'Text'#39' defaultToken='#39'comment'#39 +
            '  />'
          ''
          
            '    <Scheme name='#39'StringEscape'#39' inherit='#39'Text'#39' defaultToken='#39'str' +
            'ing'#39'>'
          '    '
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\[abfnrtv {} \[\] $ &quo' +
            't; ]'#39' />'
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\u[0-9a-fA-F]{4}'#39' priori' +
            'ty='#39'10'#39' />        '
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\o[0-7]{2}'#39' priority='#39'10' +
            #39' />        '
          
            '        <Regex token0='#39'escaped'#39' regex='#39'\\x[0-9a-fA-F]{2}'#39' priori' +
            'ty='#39'10'#39' />        '
          '        '
          '        <RegexBlock innerScheme='#39'Main'#39' start_token0='#39'default'#39' '
          '                    end_token0='#39'default'#39' >'
          ''
          '            <Start> \[  </Start>        '
          '            <End> \] </End>        '
          '        </RegexBlock>'
          '        '
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'String'#39' inherit='#39'StringEscape'#39' defaultToken='#39's' +
            'tring'#39'>'
          '        <Regex token0='#39'quotedVariable'#39' regex='#39'\$\w+'#39' />    '
          '        '
          
            '        <RegexBlock innerScheme='#39'StringNoSubst'#39' start_token0='#39'st' +
            'ring'#39' '
          '                    end_token0='#39'string'#39' >'
          ''
          '            <Start> \{  </Start>        '
          '            <End> \} </End>        '
          '        </RegexBlock>'
          '        '
          '    </Scheme>'
          ''
          
            '    <Scheme name='#39'StringNoSubst'#39' inherit='#39'StringEscape'#39' defaultT' +
            'oken='#39'string'#39'>'
          '        <RegexBlock innerScheme='#39'String'#39' start_token0='#39'string'#39' '
          '                    end_token0='#39'string'#39' >'
          ''
          '            <Start> &quot;  </Start>        '
          '            <End> &quot; </End>        '
          '        </RegexBlock>'
          '    '
          '    </Scheme>'
          ''
          '    '
          '    <Scheme name='#39'Main'#39'     '
          '            defaultToken='#39'default'#39'           '
          ''
          '            keywordsIgnoreCase='#39'false'#39
          '    >'
          '        <KeywordRegex>\b[a-zA-Z_][\w_]*\b</KeywordRegex>'
          ''
          '        <Keywords>    '
          '             break      case     catch'
          '             continue   for      foreach'
          '             global     if       else'
          '             elseif     proc     return'
          '             set        source   switch'
          '             unset      uplevel  upvar'
          '             variable   while    namespace'
          ''
          '             puts   '
          '             after      append   bgerror'
          '             binary     array    cd'
          '             clock      close    concat'
          '             eof        error    eval'
          '             exec       exit     expr'
          '             fblocked   fcopy    fconfigure'
          '             file       fileevent   filename'
          '             flush      format   gets'
          '             glob       history  incr'
          '             info       interp   join'
          '             lappend    library  lindex'
          '             linsert    list     llength'
          '             load       lrange   lreplace'
          '             lsearch    lsort    vwait'
          '             open       package  pid'
          '             pkg_mkindexputs     pwd'
          '             read       regexp   regsub'
          '             rename     resource scan'
          '             seek       socket   split'
          '             string     subst    tell'
          '             time       trace    update'
          ''
          '            bell       bind     bindtags'
          '            bitmap     button   canvas'
          '            checkbutton clipboard destroy'
          '            entry      event    focus'
          '            font       frame    grab'
          '            '
          '             grid       image    label'
          '             listbox    lower    menu'
          '             menubutton message  option'
          '             pack       pack-old photo'
          '             place      raise    radiobutton'
          '             scale      scrollbar selection'
          '             send       text     tk_menuBar'
          '             '
          '             tk_bindForTraversal                tk_bisque'
          '             tk_setPalette                      tk_chooseColor'
          
            '             tk_dialog                          tk_focusFollowsM' +
            'ouse'
          '             tk_focusNext                       tk_focusPrev'
          '             tk_getOpenFile                     tk_getSaveFile'
          '             tk_messageBox                      tk_optionMenu'
          '             tk_popup   tkerror  tkwait'
          '             toplevel   winfo    wm'
          '        </Keywords>'
          ''
          ''
          '        <Regex innerScheme='#39'Comment'#39' regex='#39'\#.*$'#39' />'
          ''
          
            '        <Regex token0='#39'symbol'#39' regex='#39'[   \]  {}()  \[  &gt; &lt' +
            '; ]'#39' />'
          '        <Regex token0='#39'symbol'#39' regex='#39'[-:?\~=+!^;,]'#39' />'
          ''
          '        <RegexBlock innerScheme='#39'String'#39' start_token0='#39'string'#39' '
          '                    end_token0='#39'string'#39' >'
          ''
          '            <Start> &quot;  </Start>        '
          '            <End> &quot; </End>        '
          '        </RegexBlock>'
          ''
          ''
          '        <SkipSyntaxToken token='#39'comment'#39' />'
          ''
          ''
          '        <SyntaxBlock capture="false" priority='#39'0'#39'  >'
          '            <Start> sym:{  </Start>'
          '            <End> sym:}  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> kw:else sym:{  </Start>'
          '            <End> sym:}  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> '
          '                [ kw:proc ] ( kw | id ) '
          '                sym:{ '
          
            '                        ( [^ sym:{ sym:} ]* sym:{ [^ sym:{ sym:}' +
            ' ]* sym:} )*? '
          '                        [^ sym:{ sym:} ]*'
          '                sym:} '
          '                sym:{ '
          '            </Start>'
          '            <End> sym:}  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> '
          '                [ kw:if kw:for ] '
          '                sym:{ '
          
            '                        ( [^ sym:{ sym:} ]* sym:{ [^ sym:{ sym:}' +
            ' ]* sym:} )*? '
          '                        [^ sym:{ sym:} ]*'
          '                sym:} '
          '                sym:{ '
          '            </Start>'
          '            <End> sym:}  </End>'
          '        </SyntaxBlock>'
          ''
          '        <SyntaxBlock capture="true">'
          '            <Start> '
          '                [ kw:if kw:for ] [^ sym:{ ]+'
          '                sym:{ '
          '            </Start>'
          '            <End> sym:}  </End>'
          '        </SyntaxBlock>'
          ''
          '    </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'Text'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ''
          '<SchemeList root='#39'Main'#39'>'
          ''
          '  <TokenAlias name='#39'text'#39' baseToken='#39'default'#39' />'
          '  '
          '  <Scheme name='#39'Text'#39' inherit='#39'Numbers'#39'>'
          '        <Regex token0='#39'email'#39'>'
          '            [_a-zA-Z\d\-\.]{1,40}'
          '            @ '
          '            ([_ a-z A-Z \d \-]+ '
          '            (\. [_ a-z A-Z \d \-]+ )+ )'
          '        </Regex>                '
          '  </Scheme>'
          ''
          '  <Scheme name='#39'Numbers'#39'>'
          
            '    <Regex token0='#39'number'#39'>\b (0x \d+ [lL]? | \d+ (e \d*)? [lLdD' +
            'fF]? ) \b</Regex>'
          
            '    <Regex token0='#39'number'#39'>\b [+\-]? \d+ (\. \d+)? ([eE] [+\-]? ' +
            '\d+) \b</Regex>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'Main'#39' keywordsIgnoreCase='#39'false'#39' '
          '          inherit='#39'Text'#39
          '          defaultToken='#39'text'#39'>'
          '  </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'VB'
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
          '          defaultToken='#39'default'#39'           '
          ''
          '          allIgnoreCase='#39'true'#39
          '  >'
          
            '    <KeywordRegex moreWordChars='#39'.'#39'>\b[a-zA-Z_][\w_]*\b</Keyword' +
            'Regex>'
          ''
          '    <Keywords>'
          '            Empty False Nothing Null True'
          '            Initialize Terminate'
          '            Call Class End'
          '            Public  Private'
          '            Const'
          '            Dim'
          '            '
          '            Exit'
          '            Do While Until   '
          '            Loop '
          '            Erase '
          '            Execute '
          '            ExecuteGlobal '
          '            For Each  In   To'
          '            Next '
          '            Default'
          '            '
          '            If  Then  ElseIf Else   End '
          '            '
          '            On Error Resume Next GoTo '
          '            Option Explicit '
          '            Property Get  Set Let'
          '            Randomize ReDim  Preserve'
          '            Select Case  Else'
          '            Sub'
          '            While Wend  With '
          '            CreateObject'
          '            '
          '            Not Or And Xor Eqv Imp Is Mod '
          '            '
          '    </Keywords>'
          ''
          ''
          '    <Regex innerScheme='#39'Comment'#39' regex='#39'Rem.*$'#39' />'
          '    <Regex innerScheme='#39'Comment'#39' regex=" '#39'.*$ " />'
          ''
          
            '    <Regex token0='#39'symbol'#39' regex='#39'[    \]    \[  \( \) &gt; &lt;' +
            '  &amp; ]'#39' />'
          '    <Regex token0='#39'symbol'#39' regex='#39'[-=+^;,]'#39' />'
          ''
          '    <SkipSyntaxToken token='#39'comment'#39' />'
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start> '
          
            '            [ kw:sub kw:class kw:if kw:function kw:property  kw:' +
            'select kw:with ]  '
          '        </Start>      '
          '        <End> kw:end  $0 </End>'
          '    </SyntaxBlock>'
          '        '
          '    <SyntaxBlock capture="true">'
          '        <Start>   [ kw:do ]    </Start>'
          ''
          '        <End> kw:loop  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start>   [ kw:for ]    </Start>'
          ''
          '        <End> kw:next  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start>   [ kw:while ]    </Start>'
          ''
          '        <End> kw:wend  </End>'
          '    </SyntaxBlock>'
          '  </Scheme>'
          '</SchemeList>')
      end
      item
        Name = 'XML'
        Scheme.Strings = (
          '<?xml version="1.0" encoding="UTF-8"?>'
          ' '
          '<SchemeList root='#39'Main'#39'>'
          ''
          '  <Scheme name='#39'BaseSyntax'#39'>'
          '    <Regex token0='#39'entity'#39'>'
          '        &amp;[a-zA-Z]+;'
          '    </Regex>'
          ''
          '    <RegexBlock innerScheme='#39'Comment'#39' end_token0='#39'comment'#39' >'
          '        <Start> &lt; !--  </Start>        '
          '        <End> --&gt; </End>        '
          '    </RegexBlock>'
          ''
          '  </Scheme>'
          ''
          '  <Scheme name='#39'InsideTag'#39' inherit='#39'BaseSyntax'#39'>'
          
            '    <RegexBlock innerScheme='#39'CDATA'#39' start_token0='#39'cdataTagStart'#39 +
            ' end_token0='#39'cdataTagEnd'#39' >'
          '        <Start> &lt; !\[\[CDATA  </Start>'
          '        <End> \]\] &gt; </End>        '
          '    </RegexBlock>'
          '  </Scheme>'
          '  '
          '  <Scheme name='#39'WithTags'#39' inherit='#39'Tag'#39' inherit0='#39'BaseSyntax'#39'>'
          '  '
          
            '    <RegexBlock innerScheme='#39'WithTags'#39' start_token0='#39'tagOpen'#39' en' +
            'd_token0='#39'tagClose'#39' >'
          '        <Start> &lt; ([\w:]+) </Start>        '
          '        <End> ( / &gt; ) | ( &lt; / $1 &gt; ) </End>        '
          '    </RegexBlock>  '
          ''
          
            '    <RegexBlock innerScheme='#39'InsideTag'#39' start_token0='#39'tagOpen'#39' e' +
            'nd_token0='#39'tagClose'#39' >'
          '        <Start> &gt;  </Start>        '
          '        <End> (?= &lt; [^ ! ] ) </End>        '
          '    </RegexBlock>  '
          ''
          ''
          '    <SyntaxBlock capture='#39'true'#39'>'
          '        <Start> tagOpen </Start>'
          '        <End> tagClose </End>'
          '    </SyntaxBlock>'
          '    '
          '  </Scheme>'
          ''
          '  <Scheme name='#39'Comment'#39' defaultToken='#39'comment'#39'>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'XmlDecl'#39' inherit='#39'Tag'#39'>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'CDATA'#39' defaultToken='#39'xmlCdata'#39'>'
          '    <SyntaxBlock capture='#39'true'#39'>'
          '        <Start> cdataTagStart </Start>'
          '        <End> cdataTagEnd </End>'
          '    </SyntaxBlock>  '
          '  </Scheme>    '
          '    '
          '  <Scheme name='#39'DTD'#39' defaultToken='#39'comment'#39'>               '
          '  </Scheme>'
          '    '
          '  <Scheme name='#39'AttrStringQuot'#39'>'
          '    <Regex token0='#39'attributeValue'#39'> [^ &quot; ]+</Regex>'
          '  </Scheme>'
          ''
          '  <Scheme name='#39'AttrStringApos'#39'>'
          '    <Regex token0='#39'attributeValue'#39'> [^ &apos; ]+</Regex>'
          '  </Scheme>'
          '    '
          '  <Scheme name='#39'Tag'#39'>  '
          '  '
          '    <Regex token0='#39'attributeName'#39' priority='#39'10'#39'>'
          '        \b[\w+\-] \s* = \s*        '
          '    </Regex>'
          ''
          '    <Regex token0='#39'attributeValue'#39'>'
          '        [^ &lt; &gt; &quot; &apos; = \s ]+         '
          '    </Regex>'
          ''
          
            '    <RegexBlock innerScheme='#39'AttrStringQuot'#39' start_token0='#39'attri' +
            'buteValue'#39' '
          '        end_token0='#39'attributeValue'#39' >'
          ''
          '        <Start> &quot;  </Start>        '
          '        <End> &quot; </End>        '
          '    </RegexBlock>'
          ''
          
            '    <RegexBlock innerScheme='#39'AttrStringApos'#39' start_token0='#39'attri' +
            'buteValue'#39' '
          '        end_token0='#39'attributeValue'#39' >'
          ''
          '        <Start> &apos;  </Start>        '
          '        <End> &apos; </End>        '
          '    </RegexBlock>'
          ''
          '  </Scheme>'
          '  '
          '  <TokenAlias name='#39'htmlText'#39' baseToken='#39'default'#39'/>'
          '  '
          '  <Scheme name='#39'Main'#39' defaultToken='#39'htmlText'#39
          '          inherit='#39'BaseSyntax'#39'        '
          '          inherit0='#39'WithTags'#39'      '
          '          keywordsIgnoreCase='#39'true'#39' >'
          '                    '
          ''
          
            '    <RegexBlock innerScheme='#39'DTD'#39' start_token0='#39'dtdTagStartEnd'#39' ' +
            'end_token0='#39'dtdTagStartEnd'#39' >'
          '        <Start> &lt; !\w+  </Start>        '
          '        <End> &gt; </End>        '
          '    </RegexBlock>'
          '                    '
          '    <Regex token0='#39'tagClose'#39'>'
          '        &lt; / [\w:]+ \s* &gt;'
          '    </Regex>'
          ''
          
            '    <RegexBlock innerScheme='#39'XmlDecl'#39' start_token0='#39'xmlDeclStart' +
            #39' end_token0='#39'xmlDeclEnd'#39' >'
          '        <Start> &lt; \? xml  </Start>'
          '        <End> \? &gt; </End>        '
          '    </RegexBlock>'
          ''
          ''
          '  </Scheme>'
          '</SchemeList>')
      end
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
          '          defaultToken='#39'default'#39'           '
          ''
          '          allIgnoreCase='#39'true'#39
          '  >'
          
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
          '        ELSE'
          '        ENDGAME'
          '        ENDREPEAT'
          '        ENDSPRITE'
          '        ENDIF'
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
          ''
          '    <Regex innerScheme='#39'Comment'#39' regex='#39'Rem.*$'#39' />'
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
          
            '            [ kw:sub kw:class kw:if kw:function kw:property  kw:' +
            'select kw:with ]  '
          '        </Start>      '
          '        <End> kw:end  $0 </End>'
          '    </SyntaxBlock>'
          '        '
          '    <SyntaxBlock capture="true">'
          '        <Start>   [ kw:do ]    </Start>'
          ''
          '        <End> kw:loop  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start>   [ kw:for ]    </Start>'
          ''
          '        <End> kw:next  </End>'
          '    </SyntaxBlock>'
          ''
          '    <SyntaxBlock capture="true">'
          '        <Start>   [ kw:while ]    </Start>'
          ''
          '        <End> kw:wend  </End>'
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
          #9'<Token name="attributeName" textColor="#583485"/>'
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
      end>
    ActiveSyntaxScheme = 'AGD'
    ActiveColorScheme = 'default'
    Left = 64
    Top = 48
  end
  object Actions: TActionList
    Left = 168
    Top = 48
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
      ImageIndex = 0
      OnExecute = actUndoExecute
      OnUpdate = actUndoUpdate
    end
    object actRedo: TEditUndo
      Category = 'Edit'
      Caption = '&Redo'
      Hint = 'Redo'
      ImageIndex = 1
      OnExecute = actRedoExecute
    end
    object actBmkSet_4: TAction
      Tag = 4
      Category = 'Bookmarks'
      Caption = 'actBmkSet_4'
      ShortCut = 24628
    end
    object actToggleShowLineEnds: TAction
      Category = 'Settings'
      Caption = 'Show line ends'
      OnExecute = actToggleShowSpacesExecute
    end
    object actToggleShowTabs: TAction
      Category = 'Settings'
      Caption = 'Show tabs'
      OnExecute = actToggleShowSpacesExecute
    end
    object actNoWrap: TAction
      Category = 'Settings'
      Caption = 'No wrap'
      OnExecute = actNoWrapExecute
    end
    object actWrapToWindow: TAction
      Category = 'Settings'
      Caption = 'Wrap to window'
    end
    object actWrapToRuler: TAction
      Category = 'Settings'
      Caption = 'Wrap to ruler'
      OnExecute = actNoWrapExecute
    end
    object actBmkSet: TAction
      Category = 'Bookmarks'
      Caption = 'Set bookmark'
      ImageIndex = 3
    end
    object actBmkDeleteLast: TAction
      Category = 'Bookmarks'
      Caption = 'Delete bookmark'
      ImageIndex = 10
    end
    object actBmkDeleteAll: TAction
      Category = 'Bookmarks'
      Caption = 'Clear bookmarks'
      ImageIndex = 2
    end
    object actToggleUseTabs: TAction
      Category = 'Settings'
      Caption = 'Use tabs'
    end
    object actToggleShowSpaces: TAction
      Category = 'Settings'
      Caption = 'Show whitespaces'
      OnExecute = actToggleShowSpacesExecute
    end
    object actToggleAutoIndent: TAction
      Category = 'Settings'
      Caption = 'Auto indent'
      OnExecute = actToggleAutoIndentExecute
    end
    object actGoToLine: TAction
      Category = 'Edit'
      Caption = 'Go to line'
      ShortCut = 16455
      OnExecute = actGoToLineExecute
    end
    object actToggleSplit: TAction
      Category = 'View'
      Caption = 'Split'
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
      OnExecute = actSearchExecute
    end
    object actReplace: TAction
      Category = 'Edit'
      Caption = 'actReplace'
      OnExecute = actReplaceExecute
    end
    object actSaveFile: TAction
      Category = 'File'
      Caption = 'Save'
      ImageIndex = 13
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
      ShortCut = 16451
      OnExecute = actCopyExecute
    end
    object actPaste: TAction
      Category = 'Edit'
      Caption = 'Paste'
      ShortCut = 16470
      OnExecute = actPasteExecute
    end
    object actCut: TAction
      Category = 'Edit'
      Caption = 'Cut'
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
      ShortCut = 114
      OnExecute = actSearchNextExecute
    end
    object actKeybindings: TAction
      Category = 'Settings'
      Caption = 'Edit key bindings'
      OnExecute = actKeybindingsExecute
    end
    object actToggleCursorBound: TAction
      Category = 'Settings'
      Caption = 'Cursor bound to chars'
      OnExecute = actToggleCursorBoundExecute
    end
    object actToggleShowRuler: TAction
      Category = 'Settings'
      Caption = 'Show ruler'
      OnExecute = actToggleShowRulerExecute
    end
    object actFont: TAction
      Category = 'Settings'
      Caption = 'Font...'
      OnExecute = actFontExecute
    end
  end
  object FontDialog: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Left = 480
    Top = 162
  end
end
