package assignment;

// 어휘 분석 관련 클래스
public class Lex {
	public String line;		// 현재 파싱하는 줄
    public int pos;			// 현재 파싱하는 글자
    public String next_token;
    public String token_string;
    
    public Lex(String line) {
        this.line = line;
        this.pos = 0;

        this.next_token = Token.EOI;  // 일단 EOI로 초기화
        this.token_string = "";   
    }
    
    // 공백 건너뛰는 메서드
    public void skip() {
        while (pos < line.length() && line.charAt(pos) <= 32) {
            pos++;
        }
    }

    
    public void lexer() {
        skip();		// 일단 공백 건너뛰기 

        if (pos >= line.length()) { 	// 만약 입력 끝나면
            this.token_string = "";		// 빈 문자열이랑 EOI 저장 후 종료
            this.next_token = Token.EOI;
            return; 
        }

        char c = line.charAt(pos);   // 현재 글자 저장
   
        if (Character.isLetter(c) || c == '_') { 	// ID 속성으로 시작하면
            int start = pos;
            pos++;
            
            // 한 줄 안에 있으면서 ID의 속성을 만족하면 다음 글자로
            while (pos < line.length() && 
            		(Character.isLetterOrDigit(line.charAt(pos)) || line.charAt(pos) == '_')) {
            	pos++;
            }

            this.token_string = line.substring(start, pos);		// 파싱 끝나면 저장
            this.next_token = Token.ID;  		// 토큰 정보 저장
        }
        else if (Character.isDigit(c)) { 			// 숫자로 시작하면
            int start = pos;
            pos++;
            
            // 한 줄 안에 있으면서 숫자이면 다음 글자로
            while (pos < line.length() && Character.isDigit(line.charAt(pos))) {
                pos++;
            }

            this.token_string = line.substring(start, pos);   // 파싱 끝나면 저장
            this.next_token = Token.CONST;  // 토큰 정보 저장
        } 
        else if (c == ':') {			// ':'을 식별했을 때
            if (pos + 1 < line.length() && line.charAt(pos + 1) == '=') {  // 다음꺼 '='이면
                this.token_string = ":=";   // 문자열이랑 토큰 저장
                this.next_token = Token.ASSIGN_OP;  
                pos += 2; 
            } else {   			// 그냥 ':' 이면 unknown
                this.token_string = String.valueOf(c);
                this.next_token = Token.UNKNOWN;
                pos++;
            }
        
        } else if (c == ';') {
            this.token_string = String.valueOf(c);
            this.next_token = Token.SEMI_COLON;
            pos++;

        } else if (c == '+' || c == '-') { 
            this.token_string = String.valueOf(c);
            this.next_token = Token.ADD_OP;
            pos++;
        
        } else if (c == '*' || c == '/') {
            this.token_string = String.valueOf(c);
            this.next_token = Token.MUL_OP;
            pos++;

        } else if (c == '(') { 
            this.token_string = String.valueOf(c);
            this.next_token = Token.LEFT_PAREN;
            pos++;

        } else if (c == ')') { 
            this.token_string = String.valueOf(c);
            this.next_token = Token.RIGHT_PAREN;
            pos++;
            
        } else { 
            this.token_string = String.valueOf(c);
            this.next_token = Token.UNKNOWN;
            pos++;
        }
    }
}
