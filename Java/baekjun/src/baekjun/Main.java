package baekjun;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;

import java.util.Collections;

// Main으로 클래스 이름 변경
public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // br.readLine() : 개행문자 전까지 한 줄 읽어옴
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        // bw.write() : 버퍼에 출력할 거 모으기
        // bw.flush() : 한번에 출력

        // StringTokenizer st = new StringTokenizer( 입력받은 값 : String);
        // st.nextToken() 으로 공백 기준으로 값 읽기
        int M = Integer.parseInt(br.readLine());
        ArrayList<Integer> arr = new ArrayList<>();

        for (int i = 0; i < M; i++) {
            String input = br.readLine();
            StringTokenizer st = new StringTokenizer(input);
            String order = st.nextToken();
            if (st.hasMoreTokens() == false) {
                if (order.equals("all")) {
                    arr.clear();
                    for (int j = 1; j <= 20; j++) {
                        arr.add(j);
                    }
                }
                 else if (order.equals("empty")) {
                    arr.clear();
                }
                continue;
            }
            int num = Integer.parseInt(st.nextToken());

            if (order.equals("add")) {
                arr.add(num);
                if (arr.size() != 1) {
                    int idx = arr.size() - 1;
                    while (arr.get(idx - 1) > arr.get(idx)) {
                        int temp = arr.get(idx - 1);
                        arr.set(idx - 1, arr.get(idx));
                        arr.set(idx, temp);
                        if (idx == 1)
                            break;
                        idx--;
                    }
                }
            } else if (order.equals("remove")) {
                if (Collections.binarySearch(arr, num) < 0) {
                    continue;
                } else {
                    arr.remove(Collections.binarySearch(arr, num));
                }
            } else if (order.equals("check")) {
                if (Collections.binarySearch(arr, num) < 0) {
                    bw.write("0\n");
                } else {
                    bw.write("1\n");
                }
            } else if (order.equals("toggle")) {
                if (Collections.binarySearch(arr, num) < 0) {
                    arr.add(num);
                    if (arr.size() != 1) {
                        int idx = arr.size() - 1;
                        while (arr.get(idx - 1) > arr.get(idx)) {
                            int temp = arr.get(idx - 1);
                            arr.set(idx - 1, arr.get(idx));
                            arr.set(idx, temp);
                            if (idx == 1)
                                break;
                            idx--;
                        }
                    }
                } else {
                    arr.remove(Collections.binarySearch(arr, num));
                }
            }
        }
        br.close();
        bw.close();
    }
}
