package com.example.pineapple.entity;

import lombok.Getter;

@Getter
public enum BusinessStatus {
    OPEN("영업 중"),
    CLOSED("영업 종료"),
    BREAK_TIME("브레이크 타임"),
    DAY_OFF("정기 휴무"),
    PREPARING("준비 중");

    private final String description;

    BusinessStatus(String description) {
        this.description = description;
    }
}