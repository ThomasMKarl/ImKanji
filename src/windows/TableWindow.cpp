#include "TableWindow.hpp"


constexpr auto numberOfKanji = 540ULL;

// clang-format off
constexpr std::array<const char *, numberOfKanji> kanjiList{
    "人", "本", "日", "一", "二", "三", "四", "五", "六", "七", "八", "九", "十", "時", "分", "半", "今", "何", "行",
    "来", "学", "大", "生", "先", "友", "語", "英", "曜", "月", "火", "水", "木", "金", "土", "週", "毎", "間", "口",
    "東", "西", "南", "北", "門", "入", "出", "会", "見", "円", "百", "千", "万", "買", "店", "屋", "京", "駅", "車",
    "電", "止", "小", "高", "安", "新", "古", "物", "食", "飲", "飯", "上", "下", "中", "外", "前", "後", "右", "左",
    "午", "父", "母", "兄", "弟", "姉", "妹", "男", "女", "子", "気", "元", "天", "雨", "休", "山", "川", "田", "海",
    "旅", "名", "字", "漢", "文", "作", "言", "話", "読", "書", "聞", "社", "家", "族", "所", "住", "近", "両", "親",
    "主", "内", "都", "県", "市", "区", "町", "村", "番", "号", "様", "思", "国", "州", "立", "校", "公", "私", "地",
    "方", "際", "部", "年", "春", "夏", "秋", "冬", "朝", "昼", "夕", "晩", "夜", "帰", "寝", "起", "着", "待", "持",
    "使", "多", "少", "々", "開", "閉", "始", "終", "貸", "教", "返", "売", "去", "末", "乗", "降", "通", "道", "歩",
    "急", "線", "鉄", "場", "目", "科", "室", "借", "知", "強", "勉", "習", "練", "事", "仕", "好", "歌", "音", "楽",
    "曲", "絵", "画", "映", "真", "写", "肉", "牛", "鳥", "魚", "米", "茶", "理", "料", "切", "洗", "色", "形", "白",
    "黒", "赤", "青", "長", "短", "明", "広", "心", "手", "紙", "活", "忙", "早", "伝", "送", "運", "度", "同", "違",
    "正", "意", "味", "宿", "題", "問", "質", "答", "留", "授", "業", "卒", "論", "試", "験", "期", "礼", "失", "婚",
    "結", "約", "合", "相", "性", "式", "全", "世", "界", "院", "病", "痛", "疲", "体", "頭", "耳", "足", "力", "熱",
    "薬", "回", "治", "政", "経", "済", "史", "歴", "育", "法", "研", "究", "関", "係", "花", "林", "森", "石", "庭",
    "池", "湖", "島", "風", "空", "泳", "遊", "園", "館", "寺", "図", "橋", "工", "交", "役", "港", "階", "飛", "渡",
    "職", "農", "商", "漁", "産", "者", "医", "員", "師", "記", "婦", "夫", "機", "器", "品", "動", "自", "受", "変",
    "消", "信", "台", "点", "枚", "美", "重", "計", "化", "用", "以", "対", "反", "要", "必", "便", "利", "続", "進",
    "決", "集", "残", "働", "考", "調", "選", "泊", "予", "定", "泣", "笑", "感", "忘", "困", "取", "死", "殺", "配",
    "悪", "悲", "苦", "最", "初", "不", "無", "有", "的", "第", "数", "和", "洋", "非", "課", "代", "費", "実", "態",
    "現", "表", "発", "類", "種", "由", "平", "原", "制", "資", "果", "説", "別", "特", "報", "告", "比", "増", "加",
    "減", "刀", "良", "周", "馬", "銀", "貝", "弓", "虫", "首", "犬", "豚", "野", "菜", "未", "転", "央", "羊", "服",
    "矢", "糸", "氏", "羽", "遠", "暑", "寒", "軽", "低", "弱", "暗", "太", "豆", "光", "押", "引", "士", "官", "昔",
    "民", "注", "顔", "声", "竹", "戸", "堂", "建", "丸", "冷", "甘", "汚", "卵", "皿", "酒", "塩", "付", "片", "焼",
    "固", "個", "怒", "幸", "恥", "辛", "眠", "念", "情", "覚", "徒", "復", "皆", "彼", "荷", "届", "払", "濯", "踊",
    "宅", "祭", "戦", "争", "律", "義", "議", "党", "涼", "暖", "静", "込", "連", "窓", "側", "葉", "景", "吉", "共",
    "供", "若", "老", "息", "娘", "奥", "将", "祖", "招", "歳", "冊", "億", "段", "倍", "次", "他", "勝", "負", "賛",
    "成", "絶", "辞", "投", "束", "守", "過", "夢", "速", "遅", "駐", "船", "座", "席", "陸", "神", "申", "査", "談",
    "王", "案", "君", "達", "星", "雪", "直", "危"};
// clang-format on

constexpr std::array<std::pair<unsigned int, unsigned int>, 7> beginEnd{
  std::make_pair<unsigned int, unsigned int>(1, 28),
  std::make_pair<unsigned int, unsigned int>(29, 100),
  std::make_pair<unsigned int, unsigned int>(101, 172),
  std::make_pair<unsigned int, unsigned int>(173, 244),
  std::make_pair<unsigned int, unsigned int>(245, 316),
  std::make_pair<unsigned int, unsigned int>(317, 460),
  std::make_pair<unsigned int, unsigned int>(461, 560)
};

void imkanji::window::Table::table(unsigned int number, unsigned int step, String & selected) const
{
  assert(number < beginEnd.size());
  ImGui::Separator();
  auto begin = beginEnd[number].first - 1;
  if (ImGui::CollapsingHeader((std::to_string(beginEnd[number].first) + " - " + std::to_string(beginEnd[number].second)).c_str()))
  {
    pushFont(2);
    for (unsigned int index = begin; index < beginEnd[number].second; ++index)
    {
      if ((index - begin) % step != 0)
        ImGui::SameLine();
      if (ImGui::Button(kanjiList[index]))
        selected = kanjiList[index];
    }
    ImGui::PopFont();
  }
}

void imkanji::window::Table::draw(const char * title, bool * p_open)
{
  String newselect = selected;

  if (!ImGui::Begin(title, p_open))
  {
    ImGui::End();
    return;
  }

  if (selected.empty())
    ImGui::Text(" ");
  else
  {
    scaleFont(1.5f);
    ImGui::Text("Selected: ");
    scaleFont(1.0f);
    ImGui::SameLine();
    pushFont(3);
    ImGui::Text(selected.c_str());
    ImGui::PopFont();
  }

  unsigned int number{0};
  table(number++, 12, newselect);
  table(number++, 12, newselect);
  table(number++, 12, newselect);
  table(number++, 12, newselect);
  table(number++, 24, newselect);
  table(number++, 24, newselect);

  if (selected != newselect)
  {
    std::swap(selected, newselect);
    notify(*this, "selected");
  }

  ImGui::Separator();
  ImGui::End();
}
