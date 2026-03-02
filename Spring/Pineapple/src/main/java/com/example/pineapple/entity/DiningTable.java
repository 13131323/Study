package com.example.pineapple.entity;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import java.time.LocalDateTime;

@Entity
@Getter
@Setter
@NoArgsConstructor
public class DiningTable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "restaurant_id")
    private Restaurant restaurant;

    private Integer tableNumber;    //테이블 번호

    @Column(nullable = false)
    private boolean isOccupied = false; //현재 사용 중 여부 (결제 시 false로 변경)

    private LocalDateTime orderStartTime; //주문 시작 시간 (타이머 및 TOP 3 계산용)

    private String seatType; //선호 좌석 정보
}
