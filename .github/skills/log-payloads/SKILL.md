---
name: log-payloads
description: Payload-specific schema rules for F001, F002, and F003 records.
---

# ペイロード定義

このスキルは、各ログ種別ごとのペイロード構造を確認するときに使う。

## 1. 仕様の参照先
- 共通のレコード仕様: spec/log-record-spec.yaml
- 各種別のペイロード仕様: spec/payloads/f001.yaml, spec/payloads/f002.yaml, spec/payloads/f003.yaml

## 2. 種別ごとの対応
- F001: spec/payloads/f001.yaml
- F002: spec/payloads/f002.yaml
- F003: spec/payloads/f003.yaml

## 3. 変更時の方針
- payload の意味を変える場合は、まず YAML を更新する。
- その後、対応する生成・解析処理を更新する。
- 種別ごとのロジックは、レコード共通層から分離して扱う。

## 4. 実装時の注意
- payload の内容は種別依存であるため、kind と payload 仕様を必ず照合する。
- 仕様変更は 1 種別ごとに小さく分けて管理する。
- 既存の C 実装で扱う場合は、読みやすさと保守性を優先する。
