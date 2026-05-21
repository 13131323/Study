package com.example.localclinic.entity;

import jakarta.persistence.*;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.NoArgsConstructor;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Entity
@Getter
@NoArgsConstructor(access = AccessLevel.PROTECTED)
public class Waiting extends BaseTimeEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "member_id", nullable = false)
    private Member member;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "hospital_id", nullable = false)
    private Hospital hospital;

    @Column(nullable = false)
    private Integer waitingNum;

    @Enumerated(EnumType.STRING)
    @Column(nullable = false)
    private WaitingType waitingType;    // SCHEDULED, IMMEDIATE

    @Column(nullable = false)
    private LocalDateTime targetAt;

    @Enumerated(EnumType.STRING)
    @Column(nullable = false)
    private WaitingStatus waitingStatus;    // PENDING, WAITING, COMPLETED, CANCELED

    // 양방향 매핑
    @OneToMany(mappedBy = "waiting", cascade = CascadeType.ALL)
    private List<Symptom> symptoms = new ArrayList<>();

    @OneToOne(mappedBy = "waiting", cascade = CascadeType.ALL, fetch = FetchType.LAZY)
    private Review review;
}