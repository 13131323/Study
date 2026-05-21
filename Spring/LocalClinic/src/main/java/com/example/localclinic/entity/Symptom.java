package com.example.localclinic.entity;

import jakarta.persistence.*;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Entity
@Getter
@NoArgsConstructor(access = AccessLevel.PROTECTED)
public class Symptom {

    @Id
    private Long id;

    @MapsId
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "waiting_id", nullable = false)
    private Waiting waiting; // 어느 대기에 속한 증상인지

    @Column(nullable = false, columnDefinition = "TEXT")
    private String content; // 증상 내용
}