package com.example.localclinic.entity;

import jakarta.persistence.*;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Entity
@Getter
@NoArgsConstructor(access = AccessLevel.PROTECTED)
public class Review extends BaseTimeEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "member_id", nullable = false)
    private Member member; // 리뷰 작성자

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "hospital_id", nullable = false)
    private Hospital hospital; // 리뷰 대상 병원

    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "waiting_id", nullable = false, unique = true)
    private Waiting waiting; // 어느 대기/예약 건에 대한 리뷰인지 (1:1 강제)

    @Column(nullable = false)
    private Integer rating; // 별점 (예: 1~5)

    @Column(nullable = false, columnDefinition = "TEXT")
    private String content; // 리뷰 내용
}